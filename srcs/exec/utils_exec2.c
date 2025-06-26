/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:56:33 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 09:58:50 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	safe_close(int fd)
{
	if (fd > -1)
		close(fd);
}

void	setup_middle_even_cmd(int pipefd1[2], int pipefd2[2])
{
	if (dup2(pipefd2[0], STDIN_FILENO) == -1)
		perror("dup2 failed (cmd even input)");
	if (dup2(pipefd1[1], STDOUT_FILENO) == -1)
		perror("dup2 failed (cmd even output)");
}

void	setup_middle_odd_cmd(int pipefd1[2], int pipefd2[2])
{
	if (dup2(pipefd1[0], STDIN_FILENO) == -1)
		perror("dup2 failed (cmd odd input)");
	if (dup2(pipefd2[1], STDOUT_FILENO) == -1)
		perror("dup2 failed (cmd odd output)");
}

void	setup_last_cmd(int i, int pipefd1[2], int pipefd2[2])
{
	if (i % 2 == 0)
	{
		if (dup2(pipefd2[0], STDIN_FILENO) == -1)
			perror("dup2 failed (last even input)");
	}
	else
	{
		if (dup2(pipefd1[0], STDIN_FILENO) == -1)
			perror("dup2 failed (last odd input)");
	}
}

void	setup_pipe(int i, int pipe_quo, int pipefd1[2], int pipefd2[2])
{
	if (i == 0)
	{
		if (dup2(pipefd2[1], STDOUT_FILENO) == -1)
			perror("dup2 failed (cmd 0 output)");
	}
	else if (i < pipe_quo)
	{
		if (i % 2 == 0)
			setup_middle_even_cmd(pipefd1, pipefd2);
		else
			setup_middle_odd_cmd(pipefd1, pipefd2);
	}
	else
		setup_last_cmd(i, pipefd1, pipefd2);
	safe_close(pipefd1[0]);
	safe_close(pipefd1[1]);
	safe_close(pipefd2[0]);
	safe_close(pipefd2[1]);
}
