/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:27:21 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/18 15:29:40 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tab(t_data *s_k)
{
	int	i;

	i = 0;
	while (s_k->glutto_tab[i])
	{
		printf("glutto_tab[%d]: |%s|\n\n", i, s_k->glutto_tab[i]);
		i++;
	}
	return ;
}

void	print_env(t_data *s_k)
{
	int	i;

	i = 0;
	while (s_k->tab_env[i])
	{
		printf("tab_env[%d]: %s\n", i, s_k->tab_env[i]);
		i++;
	}
	return ;
}

void	print_all(t_data *s_k)
{
	print_tab(s_k);
	print_env(s_k);
	return ;
}

void print_command_list(t_cmd *cmd_list)
{
	int	i;
	int	cmd_num = 1;

	printf("\n\nIN print_command_list\n\n");
	while (cmd_list)
	{
		printf("Arguments :");
		if (cmd_list->argc == 0)
		{
			printf(" (aucun)\n");
		}
		else
		{
			for (i = 0; i < cmd_list->argc; i++)
			{
				printf(" '%s'", cmd_list->args[i]);
			}
			printf("\n");
		}
		if (cmd_list->input_file)
			printf("Fichier d'entrée : '%s'\n", cmd_list->input_file);
		else
			printf("Fichier d'entrée : (aucun)\n");

		if (cmd_list->output_file)
		{
			printf("Fichier de sortie : '%s'\n", cmd_list->output_file);
			printf("Mode d'écriture   : %s\n",
					cmd_list->here_doc ? "append (>>)" : "overwrite (>)");
		}
		else
		{
			printf("Fichier de sortie : (aucun)\n");
		}
		if (cmd_list->next)
			printf("Piped vers la commande suivante.\n");
		else
			printf("Pas de commande suivante.\n");
		printf("\n");
		cmd_list = cmd_list->next;
		cmd_num++;
	}
}
