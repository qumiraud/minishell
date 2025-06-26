/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:59:22 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 10:08:55 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_input_redirection(t_cmd *cmd, t_data *s_k, int fd)
{
	if (cmd->input_file)
	{
		if (cmd->here_doc)
		{
			fd = ft_heredoc(cmd->input_file, cmd, s_k);
			if (fd == -1)
				return (-1);
		}
		else
		{
			fd = open(cmd->input_file, O_RDONLY);
			if (fd == -1)
			{
				perror(cmd->input_file);
				return (-1);
			}
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	handle_output_redirection(t_cmd *cmd, int fd)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (!cmd->output_file)
		return (0);
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->output_file, flags, 0644);
	if (fd == -1)
	{
		perror(cmd->output_file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 (output)");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_redirection(t_cmd *cmd, t_data *s_k)
{
	if (handle_input_redirection(cmd, s_k, -1) == -1)
		return (1);
	if (handle_output_redirection(cmd, -1) == -1)
		return (1);
	return (0);
}

void	exit_in_heredoc(char *tmp, int *pipefd, t_cmd *cmd, t_data *s_k)
{
	free(tmp);
	close (pipefd[1]);
	free_cmd(cmd);
	free_data(&s_k);
	free(s_k);
	exit (g_status);
}

void	handle_heredoc_input(int pipefd[2],
				char *safeword, t_cmd *cmd, t_data *s_k)
{
	char	*tmp;

	while (1)
	{
		tmp = readline(">");
		signal(SIGINT, signal_heredoc);
		if (tmp == NULL || g_status == 130)
		{
			write(STDERR_FILENO, "\n", 1);
			exit_in_heredoc(tmp, pipefd, cmd, s_k);
		}
		if (ft_strcmp(tmp, safeword) == 1)
		{
			g_status = 0;
			exit_in_heredoc(tmp, pipefd, cmd, s_k);
			break ;
		}
		write(pipefd[1], tmp, ft_strlen(tmp));
		write(pipefd[1], "\n", 1);
		free(tmp);
	}
}
