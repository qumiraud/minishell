/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/23 11:10:53 by qumiraud         ###   ########.fr       */
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
		for (int i = 0; cmd->args[i]; i++)
			printf("arg[%d] = '%s'\n", i, cmd->args[i]);
		if (ft_is_builtin(cmd->args[0]))
			exit(ft_exec_builtin(s_k, cmd));
		else
		{
			char *pathway = ft_strdupandfree(get_way(s_k->tab_env, cmd->args));
			if (!pathway)
			{
				str_error("bash :", cmd->args[0], "command not found");
				exit(127);
			}
			execve(pathway, cmd->args, s_k->tab_env);
			perror("execve");
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
		for (int i = 0; cmd->args[i]; i++)
			printf("arg[%d] = '%s'\n", i, cmd->args[i]);
		if (ft_is_builtin(cmd->args[0]))
			exit(ft_exec_builtin(s_k, cmd));
		else
		{
			char *pathway = ft_strdupandfree(get_way(s_k->tab_env, cmd->args));
			if (!pathway)
			{
				str_error("bash :", cmd->args[0], "command not found");
				exit(127);
			}
			if (cmd->args[1] && (cmd->args[1][0] == '\'' || cmd->args[1][0] == '\"'))
				cmd->args[1] = ft_strtrim(cmd->args[1], "'\"");
			for (int i = 0; cmd->args[i]; i++)
				printf("arg[%d] = '%s'\n", i, cmd->args[i]);
			execve(pathway, cmd->args, s_k->tab_env);
			perror("execve");
			exit(1);
		}
	}

	close(s_k->pipefd1[0]);
	close(s_k->pipefd1[1]);

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (0);

	// pid_t	pid;
	// int		status;

	// if (init_pipefd(s_k->pipefd1) != 0)
	// 	return (1);
	// pid = fork();
	// if (pid == -1)
	// 	return (1);
	// else if (pid == 0)
	// {
	// 	close(s_k->pipefd1[0]);
	// 	dup2(s_k->pipefd1[1], STDOUT_FILENO);
	// 	close(s_k->pipefd1[1]);
	// 	//TODO :  check si c'est un built ou non.
	// 	//TODO :  si built-in alors appelle de la fonction sinon:
	// 	//TODO :  chercher le chemin de commande dans l'env, puis execve
	// 	ft_exec_nopipe(s_k, cmd);
	// }
	// cmd = cmd->next;
	// pid = fork();
	// if (pid == 0)
	// 	return (1);
	// else if (pid == 0)
	// {
	// 	close(s_k->pipefd1[1]);
	// 	dup2(s_k->pipefd1[0], STDIN_FILENO);
	// 	close(s_k->pipefd1[0]);
	// 	//TODO :  chercher le chemin de commande dans l'env, puis execve
	// 	ft_exec_nopipe(s_k, cmd);
	// }
	// while (wait(&status))
	// 	;
	// return (0);
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
				free_cmd(cmd);
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
		ft_exec_multipipe(s_k);
	else if (s_k->pipe_quo == 1)
		ft_exec_singlepipe(s_k, cmd);
	else if (s_k->pipe_quo == 0)
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
