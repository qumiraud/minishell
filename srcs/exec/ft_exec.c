/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/22 16:20:07 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int init_pipefd(int *pipefd)
{
	pipefd = malloc(2 * sizeof(int));
	if (pipe(pipefd) == -1)
	{
		free(pipefd);
		return (1);
	}
	return (0);
}

int	ft_exec(t_data *s_k)
{
	pid_t pid;
	int		i;

	i = 0;
	//?premier exec (STDIN--->pipefd)
	if (init_pipefd(s_k->pipefd) != 0)
		return (1); //TODO : code erreur?
	pid = fork();
	if (pid == -1)
		return(-1); //TODO : code erreur?
	else if (pid == 0)
	{
		close(s_k->pipefd[0]);
		dup2(s_k->pipefd[1], STDOUT_FILENO);
		close(s_k->pipefd);
		//TODO : chercher le chemin de commande dans l'env, puis execve
	}
	//?premier exec (STDIN--cmd-->pipefd[1])


	//*boucle exec (pipefd[0]--cmd-->pipefd[1])
	while (i < s_k->pipe_nbr)
	{
		//init_pipefd                            //*
		// if (s_k->pipefd)                     //*--------->pas forcement necessaire peut etre peut on utiliser un seul pipe
		// 	free(s_k->pipefd);                 //*
		// if (init_pipefd(*s_k->pipefd) != 0)//*
		// 	return (1); /TODO : code erreur? //*
		//init_pipefd_end                   //*
		//exec_loop(s_k){                  //*
		pid = fork();
		if (pid == -1)
			return(-1); //TODO : code erreur?
		else if (pid == 0)
		{
			close(s_k->pipefd[1]);
			dup2(s_k->pipefd[0], STDIN_FILENO);
			close(s_k->pipefd[0]);
			open(s_k->pipefd[1], O_RDWR);
			dup2(s_k->pipefd[1], STDOUT_FILENO);
			close(s_k->pipefd[1]);
			//TODO : chercher le chemin de commande dans l'env, puis execve

		}
		//exec_loop_end }
		i++;
	}
	//*boucle exec (pipefd[0]--cmd-->pipefd[1])


	//?dernier exec (pipefd[0]--cmd-->STDOUT)
	pid = fork();
	if (pid == -1)
		return (-1); //TODO : code erreur ?
	else if (pid == 0)
	{
		close(s_k->pipefd[1]);
		dup2(s_k->pipefd[0], STDIN_FILENO);
		close(s_k->pipefd[0]);
		//TODO : chercher le chemin de commande dans l'env, puis execve
	}
	//?dernier exec (pipefd[0]--cmd-->STDOUT)
	while (wait(NULL))
		;
	free(s_k->pipefd);
}
