/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:56:52 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 10:12:02 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_heredoc_child(int pipefd[2],
			char *safeword, t_cmd *cmd, t_data *s_k)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		handle_heredoc_input(pipefd, safeword, cmd, s_k);
		close(pipefd[1]);
		exit(0);
	}
	return (pid);
}

int	ft_heredoc(char *safeword, t_cmd *cmd, t_data *s_k)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = create_heredoc_child(pipefd, safeword, cmd, s_k);
	if (pid == -1)
		return (-1);
	close(pipefd[1]);
	waitpid(pid, &g_status, 0);
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
		ft_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd();
	else if (ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd->args, &s_k->tab_env);
	else if (ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd->args, &s_k->tab_env, 0, 0);
	else if (ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd->args, &s_k->tab_env);
	else if (ft_strcmp(cmd->args[0], "env"))
		ft_env(s_k->tab_env);
	return (0);
}
