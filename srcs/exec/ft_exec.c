/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/23 15:24:06 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

int	init_pipefd(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

int ft_exec_multipipe(t_data *s_k, t_cmd *cmd)
{
	pid_t	pid;
	int		i = 0;
	int		status;
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
				exit(ft_exec_builtin(s_k, current_cmd));
			else
			{
				pathway = get_way(s_k->tab_env, current_cmd->args);
				if (!pathway)
				{
					str_error("bash :", current_cmd->args[0], "command not found");
					exit(127);
				}
				execve(pathway, current_cmd->args, s_k->tab_env);
				str_error("bash :", current_cmd->args[0], "command not found");
				exit(1);
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
	// Fermer la dernière pipe de lecture si elle existe
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	// Attendre tous les enfants
	while (wait(&status) > 0)
		;
	return 0;
}



// int	ft_exec_multipipe(t_data *s_k, t_cmd *cmd)
// {
// 	pid_t pid;
// 	int		i;
// 	int		status;

// 	i = 0;
// 	if (init_pipefd(s_k->pipefd1) != 0 || init_pipefd(s_k->pipefd2) != 0)
// 		return (1); //TODO : code erreur?
// 	while (cmd)
// 	{
// 		printf("test && pipe_quo=%d\n",s_k->pipe_quo);
// 		if (i % 2 == 0)
// 		{
// 			if (pipe(s_k->pipefd2) == -1)
// 				return (perror("pipe"), 1);
// 		}
// 		else
// 		{
// 			if (pipe(s_k->pipefd1) == -1)
// 				return (perror("pipe"), 1);
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 			return(-1); //TODO : code erreur?
// 		else if (pid == 0)
// 		{
// 			if (!cmd || !cmd->args[0])
// 				exit(0);
// 			setup_pipe(i, s_k->pipe_quo, s_k->pipefd1, s_k->pipefd2);
// 			if (cmd->output_file || cmd->input_file)
// 				handle_redirection(cmd);
// 			if (ft_is_builtin(cmd->args[0]))
// 				exit(ft_exec_builtin(s_k, cmd));
// 			else
// 			{
// 				char *pathway = ft_strdupandfree(get_way(s_k->tab_env, cmd->args));
// 				if (!pathway)
// 				{
// 					str_error("bash :", cmd->args[0], "command not found");
// 					exit(127);
// 				}
// 				execve(pathway, cmd->args, s_k->tab_env);
// 				perror("execve");
// 				exit(1);
// 			}
// 		}
// 		if (i > 0)
// 		{
// 			if ((i - 1) % 2 == 0)
// 			{
// 				close(s_k->pipefd2[0]);
// 				close(s_k->pipefd2[1]);
// 			}
// 			else
// 			{
// 				close(s_k->pipefd1[0]);
// 				close(s_k->pipefd1[1]);
// 			}
// 		}
// 		if (!cmd->next)
// 			break;
// 		cmd = cmd->next;
// 		i++;
// 	}
// 	while (wait(&status) > 0)
// 		;
// 	return (0);
// }

int	ft_exec_singlepipe(t_data *s_k, t_cmd *cmd)
{
	pid_t pid1, pid2;
	int status;

	if (init_pipefd(s_k->pipefd1) != 0)
		return (1);

	pid1 = fork();
	if (pid1 == 0)
	{
		// Commande gauche
		close(s_k->pipefd1[0]);
		dup2(s_k->pipefd1[1], STDOUT_FILENO);
		close(s_k->pipefd1[1]);

		if (cmd->output_file || cmd->input_file)
			handle_redirection(cmd);  // À écrire → open + dup2
		// for (int i = 0; cmd->args[i]; i++)
			// printf("arg[%d] = '%s'\n", i, cmd->args[i]);
		if (ft_is_builtin(cmd->args[0]))
			exit(ft_exec_builtin(s_k, cmd));
		else
		{
			char *pathway = get_way(s_k->tab_env, cmd->args);
			if (!pathway)
			{
				str_error("bash :", cmd->args[0], "command not found");
				exit(127);
			}
			if (execve(pathway, cmd->args, s_k->tab_env) == -1)
				str_error("bash :", cmd->args[0], "command not found");
			exit(1);
		}
	}
	if (!cmd->next)
		return (1);
	cmd = cmd->next;
	pid2 = fork();
	if (pid2 == 0)
	{
		// Commande droite
		close(s_k->pipefd1[1]);
		dup2(s_k->pipefd1[0], STDIN_FILENO);
		close(s_k->pipefd1[0]);

		if (cmd->output_file || cmd->input_file)
			handle_redirection(cmd);  // idem

		if (ft_is_builtin(cmd->args[0]))
			exit(ft_exec_builtin(s_k, cmd));
		else
		{
			char *pathway = get_way(s_k->tab_env, cmd->args);
			// for (int i = 0; cmd->args[i]; i++)
			// 	printf("arg[%d] = '%s'\n", i, cmd->args[i]);
			if (!pathway)
			{
				str_error("bash :", cmd->args[0], "command not found");
				exit(127);
			}

			if (execve(pathway, cmd->args, s_k->tab_env) == -1)
				str_error("bash :", cmd->args[0], "command not found");
			exit(1);
		}
	}

	close(s_k->pipefd1[0]);
	close(s_k->pipefd1[1]);

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (0);
}

int	ft_exec_nopipe(t_data *s_k, t_cmd *cmd)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	char	*pathway;


	fd_out = 0;
	fd_in = 0;
	if (ft_is_builtin(cmd->args[0]) && !cmd->input_file && !cmd->output_file)
	{
		ft_exec_builtin(s_k, cmd);
		return (0);
	}
	// printf("cmd_outputfile: %s\n", cmd->output_file);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		if (cmd->input_file)
		{
			if (cmd->here_doc == 1)
			{
				fd_in = ft_heredoc(cmd->input_file);
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			else
			{
				fd_in = open(cmd->input_file, O_RDONLY);
				// printf("Input file: %s\n", cmd->input_file);
				if (fd_in == -1)
				{
					perror("Error");
					exit(1);
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			// printf("Redirection stdin réussie vers %s\n", cmd->input_file);
		}
		if (cmd->output_file)
		{
			if (cmd->append == 0)
				fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd_out = open(cmd->output_file, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd_out == -1)
			return (1);
			dup2(fd_out, STDOUT_FILENO);
			close (fd_out);
		}
		if (ft_is_builtin(cmd->args[0]))
			ft_exec_builtin(s_k, cmd);
		else
		{
			pathway = get_way(s_k->tab_env, cmd->args);
			if (!pathway)
			{
				str_error("bash :", cmd->args[0], "command not found");
				free_data(&s_k);
				free_cmd(cmd);
				free(s_k);
				exit (127);
			}
			else if (execve(pathway, cmd->args, s_k->tab_env) == -1)
			{
				if (cmd->args[0][0] == '.' && cmd->args[0][1] == '\0')
					str_error("bash :", NULL, "filename argument required");
				else
					str_error("bash :", cmd->args[0], "command not found");
				free (pathway);
				free_data(&s_k);
				free(s_k);
			//	if (cmd)
			//		free_cmd(cmd);
				exit (127);
			}
		}
		free_data(&s_k);
		free(s_k);
		free_cmd(cmd);
		// free(cmd);
		exit(0);
	}
	else
	{
		wait (NULL);
	}
	return (0);
}

int	handle_exec(t_data *s_k, t_cmd *cmd)
{
	// printf("passage par handle_exec\n");
	if (s_k->pipe_quo > 1)
		ft_exec_multipipe(s_k, cmd);
	else if (s_k->pipe_quo == 1)
		ft_exec_singlepipe(s_k, cmd);
	else if (s_k->pipe_quo == 0)
		ft_exec_nopipe(s_k, cmd);
	return (0);
}
