/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:10:06 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/12 15:10:17 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_glutto_tab_array(t_data **s_k)
{
	if ((*s_k)->glutto_tab)
	{
		free((*s_k)->glutto_tab);
		(*s_k)->glutto_tab = NULL;
	}
}

void	free_rl_tab(t_data **s_k)
{
	if ((*s_k)->rl_tab)
	{
		free((*s_k)->rl_tab);
		(*s_k)->rl_tab = NULL;
	}
}

void	cleanup_data_tabs(t_data **s_k)
{
	if (*s_k)
	{
		free_glutto_tab_elements(s_k);
		free_glutto_tab_array(s_k);
		free_rl_tab(s_k);
	}
}

void	process_input_string_2(char *str, t_data **s_k, t_cmd *cmd)
{
	if (*str)
		handle_str(str, s_k, cmd);
}

int	handle_readline(char *str, t_data **s_k, t_cmd *cmd)
{
	process_input_string_2(str, s_k, cmd);
	cleanup_data_tabs(s_k);
	return (0);
}
