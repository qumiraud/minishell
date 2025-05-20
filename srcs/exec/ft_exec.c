/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/20 12:23:37 by qumiraud         ###   ########.fr       */
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

int	ft_exec_multipipe(t_data *s_k)
{
	pid_t pid;
	int		i;
	int		status;

	i = 0;
	if (init_pipefd(s_k->pipefd1) != 0 || init_pipefd(s_k->pipefd2) != 0)
		return (1); //TODO : code erreur?
	while (i <= s_k->pipe_nbr && s_k->pipe_nbr > 0)
	{
		printf("test && pipe_nbr=%d\n",s_k->pipe_nbr);
		//exec_loop() {
		pid = fork();
		if (pid == -1)
			return(-1); //TODO : code erreur?
		else if (pid == 0)
		{
			if (i % 2 == 0)
			{
				close(s_k->pipefd1[1]);
				if (i != 0)
					dup2(s_k->pipefd1[0], STDIN_FILENO);
				close(s_k->pipefd1[0]);
				close(s_k->pipefd2[0]);
				if (i != s_k->pipe_nbr)
					dup2(s_k->pipefd2[1], STDOUT_FILENO);
				close(s_k->pipefd2[1]);
				//TODO : chercher le chemin de commande dans l'env, puis execve
			}
			else
			{
				close(s_k->pipefd2[1]);
				if (i != 0)
					dup2(s_k->pipefd2[0], STDIN_FILENO);
				close(s_k->pipefd2[0]);
				close(s_k->pipefd1[0]);
				if (i != s_k->pipe_nbr)
					dup2(s_k->pipefd1[1], STDOUT_FILENO);
				close(s_k->pipefd1[1]);
				//TODO : chercher le chemin de commande dans l'env, puis execvs
			}
		}
		//exec_loop_end }
		i++;
	}
	close(s_k->pipefd1[0]);
	close(s_k->pipefd1[1]);
	close(s_k->pipefd2[0]);
	close(s_k->pipefd2[1]);
	while (wait(&status) > 0)
		;
	return (0);
}

int	ft_exec_singlepipe(t_data *s_k)
{
	pid_t	pid;
	int		status;

	if (init_pipefd(s_k->pipefd1) != 0)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(s_k->pipefd1[0]);
		dup2(s_k->pipefd1[1], STDOUT_FILENO);
		close(s_k->pipefd1[1]);
		//TODO :  check si c'est un built ou non.
		//TODO :  si built-in alors appelle de la fonction sinon:
		//TODO :  chercher le chemin de commande dans l'env, puis execve
	}
	pid = fork();
	if (pid == 0)
		return (1);
	else if (pid == 0)
	{
		close(s_k->pipefd1[1]);
		dup2(s_k->pipefd1[0], STDIN_FILENO);
		close(s_k->pipefd1[0]);
		//TODO :  chercher le chemin de commande dans l'env, puis execve
	}
	while (wait(&status))
		;
	return (0);
}

int	ft_exec_nopipe(t_data *s_k, t_cmd *cmd)
{
	pid_t	pid;
	int		fd1;
	char	*pathway;

	// printf("cmd_outputfile: %s\n", cmd->output_file);
	pid = fork();
	fd1 = 0; // Tout passer dans un processus fils
	if (pid == -1)
	return (1);
	else if (pid == 0)
	{
		if (!cmd->args[0] && !cmd->output_file)
		{
			// printf("passage par exec_nopipe\n");
			return (0);
		}
		if (cmd->output_file)
		{
			if (cmd->append == 0)
			{
				// printf("if - cmd->append : %d\n", cmd->append);
				fd1 = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd1 == -1)
					return (1);
				dup2(fd1, STDOUT_FILENO);
				close (fd1);

			}
			else
			{
				// printf("else - cmd->append : %d\n", cmd->append);
				fd1 = open(cmd->output_file, O_RDWR | O_CREAT | O_APPEND, 0644);
				if (fd1 == -1)
					return (1);
				dup2(fd1, STDOUT_FILENO);
				close (fd1);
			}

		}
		if (ft_is_builtin(cmd->args[0]))
			ft_exec_builtin(s_k, cmd);
			// printf("apres pathway, dans exec_nopipe\n");
		else
		{
			pathway = ft_strdup(get_way(s_k->tab_env, s_k->rl_tab));
			if (!pathway)
			{
				perror("command not found");
				free_data(&s_k);
				free_cmd(cmd);
				exit (127);
			}
			if (execve(pathway, cmd->args, s_k->tab_env) == -1)
			free (pathway);
			perror("execve:");
		}
		free_data(&s_k);
		free(s_k);
		free_cmd(cmd);
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
	if (s_k->pipe_nbr > 1)
		ft_exec_multipipe(s_k);
	else if (s_k->pipe_nbr == 1)
		ft_exec_singlepipe(s_k);
	else if (s_k->pipe_nbr == 0)
		ft_exec_nopipe(s_k, cmd);
	return (0);
}













// ! je savais pas quoi faire de l'ancienne parti
// alors je l'ai commente la nouvelle est au dessus
// 13/05/2025


// #include "../../includes/minishell.h"

// int	init_pipefd(int *pipefd)
// {
// 	pipefd = malloc(2 * sizeof(int));
// 	if (pipe(pipefd) == -1)
// 	{
// 		free(pipefd);
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_exec_multipipe(t_data *s_k)
// {
// 	pid_t pid;
// 	int		i;
// 	int		status;

// 	i = 0;
// 	if (init_pipefd(s_k->pipefd1) != 0 || init_pipefd(s_k->pipefd2) != 0)
// 		return (1); //TODO : code erreur?
// 	while (i <= s_k->pipe_nbr && s_k->pipe_nbr > 0)
// 	{
// 		// printf("test && pipe_nbr=%d\n",s_k->pipe_nbr);
// 		//exec_loop() {
// 		pid = fork();
// 		if (pid == -1)
// 			return(-1); //TODO : code erreur?
// 		else if (pid == 0)
// 		{
// 			if (i % 2 == 0)
// 			{
// 				close(s_k->pipefd1[1]);
// 				if (i != 0)
// 					dup2(s_k->pipefd1[0], STDIN_FILENO);
// 				close(s_k->pipefd1[0]);
// 				close(s_k->pipefd2[0]);
// 				if (i != s_k->pipe_nbr)
// 					dup2(s_k->pipefd2[1], STDOUT_FILENO);
// 				close(s_k->pipefd2[1]);
// 				//TODO : chercher le chemin de commande dans l'env, puis execve
// 			}
// 			else
// 			{
// 				close(s_k->pipefd2[1]);
// 				if (i != 0)
// 					dup2(s_k->pipefd2[0], STDIN_FILENO);
// 				close(s_k->pipefd2[0]);
// 				close(s_k->pipefd1[0]);
// 				if (i != s_k->pipe_nbr)
// 					dup2(s_k->pipefd1[1], STDOUT_FILENO);
// 				close(s_k->pipefd1[1]);
// 				//TODO : chercher le chemin de commande dans l'env, puis execvs
// 			}
// 		}
// 		//exec_loop_end }
// 		i++;
// 	}
// 	close(s_k->pipefd1[0]);
// 	close(s_k->pipefd1[1]);
// 	close(s_k->pipefd2[0]);
// 	close(s_k->pipefd2[1]);
// 	while (wait(&status) > 0)
// 		;
// 	free(s_k->pipefd1);
// 	free(s_k->pipefd2);
// 	return (0);
// }

// int	ft_exec_singlepipe(t_data *s_k)
// {
// 	pid_t	pid;
// 	int		status;

// 	if (init_pipefd(s_k->pipefd1) != 0)
// 		return (1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	else if (pid == 0)
// 	{
// 		close(s_k->pipefd1[0]);
// 		dup2(s_k->pipefd1[1], STDOUT_FILENO);
// 		close(s_k->pipefd1[1]);
// 		//TODO :  chercher le chemin de commande dans l'env, puis execve
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 		return (1);
// 	else if (pid == 0)
// 	{
// 		close(s_k->pipefd1[1]);
// 		dup2(s_k->pipefd1[0], STDIN_FILENO);
// 		close(s_k->pipefd1[0]);
// 		//TODO :  chercher le chemin de commande dans l'env, puis execve
// 	}
// 	while (wait(&status))
// 		;
// 	return (0);
// }

// int	ft_exec_nopipe(t_data *s_k)
// {
// 	pid_t	pid;
// 	char	*pathway;

// 	pid = fork();
// 	if (pid == -1)
// 	return (1);
// 	else if (pid == 0)
// 	{
// 		pathway = ft_strdup(get_way(s_k->tab_env, s_k->rl_tab));
// 		// printf("apres pathway, dans exec_nopipe\n");
// 	}
// 	wait (NULL);
// 	return (0);
// }

// int	handle_exec(t_data *s_k)
// {
// 	// printf("passage par handle_exec\n");
// 	if (s_k->pipe_nbr > 1)
// 		ft_exec_multipipe(s_k);
// 	//else if (s_k->pipe_nbr == 1)
// 	//	ft_exec_singlepipe(s_k);
// 	else if (s_k->pipe_nbr == 0)
// 		ft_exec_nopipe(s_k);
// 	return (0);
// }
