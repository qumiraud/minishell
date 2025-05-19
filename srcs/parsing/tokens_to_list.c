/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:53:23 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/09 11:58:26 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




t_cmd *new_cmd(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		printf ("ALED\n\n\n"); // NON
		return (0);
	}

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



t_cmd *parse_cmd(char **token)
{
	t_cmd	*head;
	t_cmd	*current;
	int		i;
	
	head = new_cmd();
	current = head;
	i = 0;

	while (token[i])
	{
		if (ft_strncmp(token[i], "|", 1) == 0)
		{
			current->next = new_cmd();
			current = current->next;
			i++;
			current->nb_ope++;
			// current->argc++;
		
		}
		else if (ft_strncmp(token[i], "<<", 2) == 0 && token[i + 1])
		{
			if (current->output_file)
			{
				free (current->output_file);
				current->output_file = NULL;
			}
			current->output_file = ft_strdup(token[i + 1]);
			current->append = 1;
			i += 2;
			current->nb_ope++;
			// current->argc++;

		}
		else if (ft_strncmp(token[i], ">>", 2) == 0 && token[i + 1])
		{
			if (current->input_file)
			{
				free (current->input_file);
				current->input_file = NULL;
			}
			current->input_file = ft_strdup(token[i + 1]);
			current->here_doc = 1;
			i += 2;
			current->nb_ope++;
			// current->argc++;

		}
		else if (ft_strncmp(token[i], "<", 1) == 0 && token[i + 1])
		{
			if (current->input_file)
			{
				free (current->input_file);
				current->input_file = NULL;
			}
			current->input_file = ft_strdup(token[i + 1]);
			i += 2;
			current->nb_ope++;
			// current->argc++; // a voir si je peux pas 
			//le mettre dans la while et pas les if 
			//agif a arg_to_cmd 09/05/2025

		}
		else if (ft_strncmp(token[i], ">", 1) == 0 && token[i + 1])
		{
			if (current->output_file)
			{
				free (current->output_file);
				current->output_file = NULL;
			}
			current->output_file = ft_strdup(token[i + 1]);
			current->append = 0;
			i += 2;
			current->nb_ope++;
			// current->argc++;

		}
		else
		{
			arg_to_cmd(current, token[i]);
			i++;
		}
		// i++;
		
	}
	return (head);
}




















































































// char *t_to_l_strdup(const char *s)
// {
// 	int i;
// 	char *copy;
	
// 	i = 0;
	
// 	while (s[i])
// 		i++;
// 	copy = malloc(i + 1);
// 	if (!copy)
// 		return NULL;
// 	i = 0;
// 	while (s[i])
// 	{
// 		copy[i] = s[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }

// void	

// void	tokenize(t_data **s_k, t_lst_arg **token)
// {
// 	int		i;

// 	i = 0;
	
// 	while ((*s_k)->rl_tab[i])
// 	{
// 		printf("rl_tab[%d]: %s\n\n",i, (*s_k)->rl_tab[i]);

// 		rl_lst_addback(token, rl_lst_new(&(*s_k)->rl_tab[i][0], (*s_k)->rl_tab[i], i));
// 		printf ("HALLO????");
// 		i++;
// 	}



	
// 	t_lst_arg	*nav;
// 	nav = (*token);
// 	i = 0;
// 	while (nav)
// 	{
// 		printf("\ntoken[%d]: %s\n\n\n\n", i, nav->rl_arg);
// 		nav = nav->next;
// 		i++;
// 	}
// }