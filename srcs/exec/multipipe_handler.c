/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:18:55 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 13:08:39 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit_in_child_p(t_data *s_k, t_cmd *cmd, int ex_code)
{
	free_cmd(cmd);
	free_data(&s_k);
	free(s_k);
	exit(ex_code);
}

int	end_of_multipipe(int *prev_pipe_read)
{
	if (*prev_pipe_read != -1)
		close(*prev_pipe_read);
	while (wait(&g_status) > 0)
		;
	return (g_status);
}

void	to_execve(t_data *s_k, t_cmd *current_cmd, t_cmd *cmd)
{
	char	*pathway;

	pathway = get_way(s_k->tab_env, current_cmd->args);
	if (!pathway)
	{
		str_error("bash :", current_cmd->args[0], "command not found");
		free_and_exit_in_child_p(s_k, cmd, 127);
	}
	if (execve(pathway, current_cmd->args, s_k->tab_env) == -1)
	{
		if (ft_strcmp(current_cmd->args[0], pathway) == 0)
			free(pathway);
		str_error("bash :", current_cmd->args[0], "command not found");
		free_and_exit_in_child_p(s_k, cmd, 127);
	}
}
