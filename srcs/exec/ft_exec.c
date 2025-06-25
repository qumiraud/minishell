/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/25 14:06:15 by qumiraud         ###   ########.fr       */
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
void	update_variable( char **str, char **env, int x, int i)
{
	char	*tmp;
	if (!str)
		return ;
	if (i == 1)
	{
		(*str)--;
		tmp = (*str);
		(*str) = ft_strdupandfree(ft_itoa(g_status));
		free(tmp);
		return;
	}
	else if (i == 2)
	{
		tmp = ft_strdup((env[x] + ft_strlen(*str) + 1));
		(*str)--;
		free(*str);
		*str = tmp;
		return;
	}
}

void	ft_expand_variable(char **str, char **env)
{
	int		strlen;
	int		i;

	i = 0;
	(*str) ++;
	if (*str[0] == '\0')
		return;
	strlen = ft_strlen(*str);
	if (ft_strcmp(*str, "?"))
	{
		update_variable(str, env, 0, 1);
		return;
	}
	while (env[i])
	{
		if (!ft_strncmp(*str, env[i], strlen) /*&& env[i][strlen + 1] == '='*/)
		{
			update_variable(str, env, i, 2);
			return;
		}
		i++;
	}
	(*str)--;
	*str[0] = '\0';
}

int	handle_exec(t_data *s_k, t_cmd *cmd)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
		while (tmp->args[i])
		{
			j = 0;
			while(tmp->args[i][j])
			{
				if (tmp->args[i][j] == '$' && tmp->args[i][j + 1] != '\0')
				{
					ft_expand_variable(&(tmp)->args[i], s_k->tab_env);
					break ;
				}
				j++;
			}
			i++;
		}
	if (s_k->pipe_quo >= 1)
		ft_exec_multipipe(s_k, cmd);
	// else if (s_k->pipe_quo == 1)
	// 	ft_exec_singlepipe(s_k, cmd);
	else if (s_k->pipe_quo == 0)
		ft_exec_nopipe(s_k, cmd);
	free_cmd(cmd);
	return (0);
}
