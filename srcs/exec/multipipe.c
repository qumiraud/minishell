/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:07:52 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/14 11:42:51 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit_in_child_p(t_data *s_k, t_cmd *cmd, int ex_code)
{
		free_cmd(cmd);
		free_data(&s_k);
		free(s_k);
		exit(ex_code);
}
int	end_of_multipipe(int *prev_pipe_read)
{
	int	status;


	if (*prev_pipe_read != -1)
		close(*prev_pipe_read);
	while (wait(&status) > 0)
		;
	return (status);
}


int	ft_exec_multipipe(t_data *s_k, t_cmd *cmd)
{
	pid_t	pid;
	int		i = 0;
	// int		status;
	int		prev_pipe_read = -1;  // Lecture de la pipe précédente
	int		current_pipe[2];      // Pipe courante
	char	*pathway;

	t_cmd *current_cmd = cmd;

	while (current_cmd)
	{
		// Créer une nouvelle pipe sauf pour la dernière commande
		if (current_cmd->next)
		{
			if (pipe(current_pipe) == -1)
			{
				perror("pipe");
				return 1;
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return 1;
		}
		if (pid == 0)
		{ // CHILD
			// Redirection d'entrée (depuis la pipe précédente)
			if (prev_pipe_read != -1)
			{
				if (dup2(prev_pipe_read, STDIN_FILENO) == -1)
				{
					perror("dup2 input");
					exit(1);
				}
				close(prev_pipe_read);
			}
			// Redirection de sortie (vers la pipe courante)
			if (current_cmd->next)
			{
				if (dup2(current_pipe[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 output");
					exit(1);
				}
				close(current_pipe[1]);
				close(current_pipe[0]);
			}
			// Gestion des redirections de fichiers
			if (current_cmd->input_file || current_cmd->output_file)
				handle_redirection(current_cmd);
			// Exécution de la commande
			if (ft_is_builtin(current_cmd->args[0]))
			{
				ft_exec_builtin(s_k, current_cmd);
				free_and_exit_in_child_p(s_k, cmd, 1);
			}
			else
			{
				pathway = get_way(s_k->tab_env, current_cmd->args);
				if (!pathway)
				{
					str_error("bash :", current_cmd->args[0], "command not found");
					free_and_exit_in_child_p(s_k, cmd, 127);
				}
				if (execve(pathway, current_cmd->args, s_k->tab_env) == -1)
				{
					if (ft_strcmp(cmd->args[0], pathway) == 0)
						free(pathway);
					str_error("bash :", current_cmd->args[0], "command not found");
					free_and_exit_in_child_p(s_k, cmd, 127);
				}
			}
		}
		// PARENT
		// Fermer l'ancienne pipe de lecture
		if (prev_pipe_read != -1)
			close(prev_pipe_read);
		// Si on a créé une nouvelle pipe, fermer l'écriture et garder la lecture
		if (current_cmd->next)
		{
			close(current_pipe[1]);  // Fermer l'écriture
			prev_pipe_read = current_pipe[0];  // Garder la lecture pour la prochaine itération
		}
		current_cmd = current_cmd->next;
		i++;
	}
	g_status = end_of_multipipe(&prev_pipe_read);
	// if (prev_pipe_read != -1)
	// 	close(prev_pipe_read);
	// while (wait(&status) > 0)
	// 	;
	return 0;
}
