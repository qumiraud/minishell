/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/20 13:10:28 by qumiraud         ###   ########.fr       */
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

void	ft_expand_variable(char **str, char **env)
{
	int		strlen;
	int		i;
	char	*tmp;

	i = 0;
	(*str) ++;
	if (*str[0] == '\0')
		return;
	strlen = ft_strlen(*str);
	while (env[i])
	{
		if (!ft_strncmp(*str, env[i], strlen) /*&& env[i][strlen + 1] == '='*/)
		{
			tmp = ft_strdup((env[i] + strlen + 1));
			*str = tmp;
			return;
		}
		i++;
	}
	// free(*str);
	*str[0] = '\0';
}

int	handle_exec(t_data *s_k, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '$' && cmd->args[i][1] != '\0')
			ft_expand_variable(&cmd->args[i], s_k->tab_env);
		i ++;
	}
	// printf("test expand\n->"); print_command_list(cmd);
	if (s_k->pipe_quo > 1)
		ft_exec_multipipe(s_k, cmd);
	else if (s_k->pipe_quo == 1)
		ft_exec_singlepipe(s_k, cmd);
	else if (s_k->pipe_quo == 0)
		ft_exec_nopipe(s_k, cmd);
	//free_cmd(cmd);
	return (0);
}
