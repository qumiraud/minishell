/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:11:29 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/18 11:16:04 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_child_cleanup_and_exit(t_data *s_k)
{
	free_data(&s_k);
	free(s_k);
	ft_exit(0);
}

void	ft_exec_builtin_child(t_data *s_k, t_cmd *cmd)
{
	ft_exec_builtin(s_k, cmd);
	free_cmd(cmd);
	free_data(&s_k);
	free(s_k);
	ft_exit(0);
}
