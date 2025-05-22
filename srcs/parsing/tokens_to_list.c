/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeten <yeten@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:44:53 by yeten             #+#    #+#             */
/*   Updated: 2025/05/22 15:23:45 by yeten            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"




t_cmd *new_cmd(void)
{
	t_cmd *cmd;

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
		return;
	}
	cmd->args[cmd->argc] = ft_strdup(arg);
	if (!cmd->args[cmd->argc])
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	cmd->argc++;
	cmd->args[cmd->argc] = NULL;
	// printf ("\n\ncmd->argc : %d\n\n", cmd->argc);
}



















static void	handle_pipe(char **token, int *i, t_cmd **current)
{
	(void)token;
		(*current)->next = new_cmd();
		*current = (*current)->next;
		(*i)++;
		(*current)->nb_ope++;
}

static void	handle_append_output(char **token, int *i, t_cmd *current)
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

static void	handle_output(char **token, int *i, t_cmd *current)
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

static void	handle_here_doc(char **token, int *i, t_cmd *current)
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

static void	handle_input(char **token, int *i, t_cmd *current)
{
		if (current->input_file)
		{
			free(current->input_file);
			current->input_file = NULL;
		}
		current->input_file = ft_strdup(token[*i + 1]);
		*i += 2;
		current->nb_ope++;
}

static int	process_token(char **token, int i, t_cmd **current)
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

static void	handle_regular_arg(char **token, int *i, t_cmd *current)
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













// t_cmd *parse_cmd(char **token)
// {
// 	t_cmd	*head;
// 	t_cmd	*current;
// 	int		i;

// 	head = new_cmd();
// 	current = head;
// 	i = 0;

// 	while (token[i])
// 	{
// 		if (ft_strncmp(token[i], "|", 1) == 0)
// 		{
// 			current->next = new_cmd();
// 			current = current->next;
// 			i++;
// 			current->nb_ope++;
// 		}
// 		else if (ft_strncmp(token[i], ">>", 2) == 0 && token[i + 1])
// 		{
// 			if (current->output_file)
// 			{
// 				free (current->output_file);
// 				current->output_file = NULL;
// 			}
// 			current->output_file = ft_strdup(token[i + 1]);
// 			current->append = 1;
// 			i += 2;
// 			current->nb_ope++;
// 		}
// 		else if (ft_strncmp(token[i], ">", 1) == 0 && token[i + 1])
// 		{
// 			if (current->output_file)
// 			{
// 				free (current->output_file);
// 				current->output_file = NULL;
// 			}
// 			current->output_file = ft_strdup(token[i + 1]);
// 			current->append = 0;
// 			i += 2;
// 			current->nb_ope++;
// 		}
// 		else if (ft_strncmp(token[i], "<<", 2) == 0 && token[i + 1])
// 		{
// 			if (current->input_file)
// 			{
// 				free (current->input_file);
// 				current->input_file = NULL;
// 			}
// 			current->input_file = ft_strdup(token[i + 1]);
// 			current->here_doc = 1;
// 			i += 2;
// 			current->nb_ope++;
// 		}
// 		else if (ft_strncmp(token[i], "<", 1) == 0 && token[i + 1])
// 		{
// 			if (current->input_file)
// 			{
// 				free (current->input_file);
// 				current->input_file = NULL;
// 			}
// 			current->input_file = ft_strdup(token[i + 1]);
// 			i += 2;
// 			current->nb_ope++;
// 		}
// 		else
// 		{
// 			arg_to_cmd(current, token[i]);
// 			i++;
// 		}
// 	}
// 	return (head);
// }









































