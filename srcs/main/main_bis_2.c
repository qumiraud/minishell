/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:25:55 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/12 13:47:26 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (cmd)
	{
		tmp = cmd->next;
		while (i < cmd->argc)
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		i = 0;
		free(cmd->input_file);
		free(cmd->output_file);
		free(cmd);
		cmd = tmp;
	}
}

void	handle_str(char *str, t_data **s_k, t_cmd *cmd)
{
	str++;
	add_history(str);
	fill_suprem_knowledge(s_k, str);
	cmd = parse_cmd((*s_k)->glutto_tab);
	print_tab(*s_k);
	print_command_list(cmd);
	handle_exec(*s_k, cmd);
}

void	handle_ending(t_data **s_k)
{
	free_s_k(s_k);
	free_glt(s_k);
	free(*s_k);
	(*s_k) = NULL;
	printf("exit\n");
}
