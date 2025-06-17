/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_list_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:15:50 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/17 15:16:52 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_here_doc(char **token, int *i, t_cmd *current)
{
	if (current->input_file)
	{
		free(current->input_file);
		current->input_file = NULL;
	}
	current->input_file = ft_strdup(token[*i + 1]);
	current->here_doc = 1;
	*i += 2;
	current->nb_ope++;
}

void	handle_input(char **token, int *i, t_cmd *current)
{
	if (current->input_file)
	{
		free(current->input_file);
		current->input_file = NULL;
	}
	current->input_file = ft_strdup(token[*i + 2]);
	*i += 2;
	current->nb_ope++;
}

int	process_token(char **token, int i, t_cmd **current)
{
	if (ft_strncmp(token[i], "|", 1) == 0)
		handle_pipe(token, &i, current);
	else if (ft_strncmp(token[i], ">>", 2) == 0 && token[i + 1])
		handle_append_output(token, &i, *current);
	else if (ft_strncmp(token[i], ">", 1) == 0 && token[i + 1])
		handle_output(token, &i, *current);
	else if (ft_strncmp(token[i], "<<", 2) == 0 && token[i + 1])
		handle_here_doc(token, &i, *current);
	else if (ft_strncmp(token[i], "<", 1) == 0 && token[i + 1])
		handle_input(token, &i, *current);
	return (i);
}

void	handle_regular_arg(char **token, int *i, t_cmd *current)
{
	arg_to_cmd(current, token[*i]);
	(*i)++;
}

t_cmd	*parse_cmd(char **token)
{
	t_cmd	*head;
	t_cmd	*current;
	int		i;
	int		old_i;

	head = new_cmd();
	current = head;
	i = 0;
	while (token[i])
	{
		old_i = i;
		i = process_token(token, i, &current);
		if (i == old_i)
			handle_regular_arg(token, &i, current);
	}
	return (head);
}
