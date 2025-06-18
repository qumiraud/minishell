/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nopipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:33:12 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/18 17:40:44 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_input(t_cmd *cmd)
{
	int	fd;

	if (cmd->here_doc)
	{
		fd = ft_heredoc(cmd->input_file);
	}
	else
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("Error");
			return (-1);
		}
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	open_output(t_cmd *cmd)
{
	int	fd;

	if (cmd->append)
		fd = open(cmd->output_file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	ft_setup_redirections(t_cmd *cmd)
{
	if (cmd->input_file)
	{
		if (open_input(cmd) < 0)
			return (-1);
	}
	if (cmd->output_file)
	{
		if (open_output(cmd) < 0)
			return (-1);
	}
	return (0);
}

void	ft_exec_external(t_data *s_k, t_cmd *cmd)
{
	char	*pathway;

	pathway = get_way(s_k->tab_env, cmd->args);
	if (!pathway)
	{
		str_error("bash :", cmd->args[0], "command not found");
		free_cmd(cmd);
		free_data(&s_k);
		free(s_k);
		ft_exit(127);
	}
	if (execve(pathway, cmd->args, s_k->tab_env) == -1)
	{
		str_error("bash :", cmd->args[0], "command not found");
		if (ft_strcmp(cmd->args[0], pathway) == 0)
			free(pathway);
		free_cmd(cmd);
		free_data(&s_k);
		free(s_k);
		ft_exit(127);
	}
}

int	ft_exec_nopipe(t_data *s_k, t_cmd *cmd)
{
	pid_t	pid;

	if (ft_is_builtin(cmd->args[0])
		&& !cmd->input_file && !cmd->output_file)
	{
		ft_exec_builtin(s_k, cmd);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		if (ft_setup_redirections(cmd) == -1)
			exit(1);
		if (ft_is_builtin(cmd->args[0]))
			ft_exec_builtin_child(s_k, cmd);
		else
			ft_exec_external(s_k, cmd);
		ft_child_cleanup_and_exit(s_k);
	}
	else
	{
		wait(&g_status);
		g_status %= 255;
	}
	printf("g_status after nopipe : %d\n", g_status);
	return (0);
}
