/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/08 13:59:01 by qumiraud         ###   ########.fr       */
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

int	ft_exec_nopipe(t_data *s_k)
{
	pid_t	pid;
	char	*pathway;

	pid = fork();
	if (pid == -1)
	return (1);
	else if (pid == 0)
	{
		pathway = ft_strdup(get_way(s_k->tab_env, s_k->rl_tab));
		printf("%s\n", pathway);
		printf("apres pathway, dans exec_nopipe\n");
	}
	wait (NULL);
	return (0);
}

int	handle_exec(t_data *s_k)
{
	printf("passage par handle_exec\n");
	if (s_k->pipe_nbr > 1)
		ft_exec_multipipe(s_k);
	//else if (s_k->pipe_nbr == 1)
	//	ft_exec_singlepipe(s_k);
	else if (s_k->pipe_nbr == 0)
		ft_exec_nopipe(s_k);
	return (0);
}
