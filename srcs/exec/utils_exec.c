/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:56:52 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/19 14:02:41 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	ft_is_redirection(char **cmd)
// {
// 	while (*cmd)
// 	{
// 		if()
// 	}
// }

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "pwd") ||
		ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "env") ||
			ft_strcmp(cmd, "export") || ft_strcmp(cmd, "unset") ||
				ft_strcmp(cmd, "exit"))
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
	// (void)s_k;
	return (0);
}