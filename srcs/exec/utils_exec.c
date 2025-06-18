/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:56:52 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/18 13:20:47 by qumiraud         ###   ########.fr       */
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

int	handle_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->input_file && !cmd->here_doc)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->input_file);
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 (input)");
			close(fd);
			exit(1);
		}
		close(fd);
	}
	else if (cmd->input_file && cmd->here_doc)
	{
		fd = ft_heredoc(cmd->input_file);
		if (fd == -1)
		{
			perror("heredoc");
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 (heredoc)");
			close(fd);
			exit(1);
		}
		close(fd);
	}
	if (cmd->output_file)
	{
		if (cmd->append)
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(cmd->output_file);
			exit(1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 (output)");
			close(fd);
			exit(1);
		}
		close(fd);
	}
	return (0);
}

int	ft_heredoc(char *safeword)
{
	char	*tmp;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (1);
	while (1)
	{
		tmp = readline(">");
		if (ft_strcmp(tmp, safeword) != 0)
		{
			free(tmp);
			break ;
		}
		write(pipefd[1], tmp, ft_strlen(tmp));
		write(pipefd[1], "\n", 1);
		free(tmp);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "pwd")
		|| ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "env")
		|| ft_strcmp(cmd, "export") || ft_strcmp(cmd, "unset")
		|| ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	ft_exec_builtin(t_data *s_k, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo"))
	{
		ft_echo(cmd->args);
		return (0);
	}
	if (ft_strcmp(cmd->args[0], "pwd"))
	{
		ft_pwd();
		return (0);
	}
	if (ft_strcmp(cmd->args[0], "cd"))
	{
		ft_cd(cmd->args, &s_k->tab_env);
		return (0);
	}
	if (ft_strcmp(cmd->args[0], "unset"))
	{
		ft_unset(cmd->args, &s_k->tab_env);
		return (0);
	}
	if (ft_strcmp(cmd->args[0], "export"))
	{
		ft_export(cmd->args, &s_k->tab_env);
		return (0);
	}
	if (ft_strcmp(cmd->args[0], "env"))
	{
		ft_env(s_k->tab_env);
		return (0);
	}
	return (0);
}
