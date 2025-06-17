/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:44:53 by yeten             #+#    #+#             */
/*   Updated: 2025/06/17 15:16:34 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->argc = 0;
	cmd->args[0] = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->here_doc = 0;
	cmd->nb_ope = 0;
	cmd->next = NULL;
	return (cmd);
}

void	arg_to_cmd(t_cmd *cmd, char *arg)
{
	if (cmd->argc >= MAX_ARGS - 1)
	{
		printf("too much args.\n");
		return ;
	}
	cmd->args[cmd->argc] = ft_strdup(arg);
	printf("cmd in arg_to_cmd: %s\n", cmd->args[cmd->argc]);
	if (!cmd->args[cmd->argc])
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	cmd->argc++;
	cmd->args[cmd->argc] = NULL;
}

void	handle_pipe(char **token, int *i, t_cmd **current)
{
	(void)token;
	(*current)->next = new_cmd();
	*current = (*current)->next;
	(*i)++;
	(*current)->nb_ope++;
}

void	handle_append_output(char **token, int *i, t_cmd *current)
{
	if (current->output_file)
	{
		free(current->output_file);
		current->output_file = NULL;
	}
	current->output_file = ft_strdup(token[*i + 1]);
	current->append = 1;
	*i += 2;
	current->nb_ope++;
}

void	handle_output(char **token, int *i, t_cmd *current)
{
	if (current->output_file)
	{
		free(current->output_file);
		current->output_file = NULL;
	}
	current->output_file = ft_strdup(token[*i + 1]);
	current->append = 0;
	*i += 2;
	current->nb_ope++;
}
