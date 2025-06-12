/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/12 10:17:07 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sig;
// volatile sig_atomic_t g_sig = 0;

void free_cmd(t_cmd *cmd)
{
	t_cmd *tmp;
	int i;

	while (cmd)
	{
		tmp = cmd->next;

		// Libération des arguments
		for (i = 0; i < cmd->argc; i++)
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
		}

		// Libération des fichiers (une seule fois par commande)
		free(cmd->input_file);
		free(cmd->output_file);

		free(cmd);
		cmd = tmp;
	}
}


void	handle_str(char *str, t_data **s_k, t_cmd *cmd)
{
	str++; // verifier que ca ne pose pas de probleme c'est pour supprimer l'espace rajouter, pour qu'il ne soit pas dans le add history
	add_history(str);
	// (*s_k)->rl_lst = (*token);
	fill_suprem_knowledge(s_k, str);
	// (*s_k)->cmd_arg = (*token);
	// re_token_wd(s_k);
	// (void)cmd;
	cmd = parse_cmd((*s_k)->glutto_tab);
	// g_sig = 0;
	
	print_tab(*s_k);
	
	print_command_list(cmd);
	// printf ("TEST LEAK >>>>>>>>>>\n\n\n");
	// g_sig = 1;

	handle_exec(*s_k, cmd);
	// free_cmd(cmd);

	// print_command_list(cmd);

}

void	handle_ending(t_data **s_k)
{
	// free_data(s_k);
	free_s_k(s_k);
	free_glt(s_k);
	free(*s_k);
	(*s_k) = NULL;
	printf("exit\n");

}

int	handle_readline(char *str, t_data **s_k, t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (*str)
		handle_str(str, s_k, cmd);
	len = (*s_k)->tab_len;
	if (*s_k)
	{
		if ((*s_k)->glutto_tab)
		{
			while (i <= len)
			{
				// printf("HALLO len \n\n %d\n\n", len);
				// printf("HALLO I \n\n %d\n\n", i);
				free((*s_k)->glutto_tab[i]);
				(*s_k)->glutto_tab[i] = NULL;
				i++;
			}
		}
		if ((*s_k)->glutto_tab)
		{
			free((*s_k)->glutto_tab);
			(*s_k)->glutto_tab = NULL;
		}
		if ((*s_k)->rl_tab)
		{
			free((*s_k)->rl_tab);
			(*s_k)->rl_tab = NULL;
		}
	}
	return (0);
}


char *input_with_space(char *str)
{
	char *new_str;

	new_str = NULL;
	if (!str)
		return (NULL);
	new_str = ft_strjoin(" ", str);
	if (!new_str)
		return (NULL);
	free (str);
	str = NULL;
	return (new_str);
}





int	main(int argc, char **argv, char **envp)
{
	t_data		*suprem_knowledge;
	t_cmd		*cmd;
	char		*str;

	str = NULL;
	cmd = NULL;
	if (argc > 1)
	{
		argv[0] = NULL;
		return (1);
	}
	init_suprem_knowledge(&suprem_knowledge, envp);
	if (!suprem_knowledge)
		return (1);
	while (1)
	{
		// g_sig = 0;
		setup_signal();
		str = readline("💾 minishell :");
		// printf ("%s\n\n", str);
		if (ft_strcmp(str, "exit") == 1)
		{
			free (str);
			str = NULL;
			handle_ending(&suprem_knowledge);

			return (0);
		}
		if (!str)
		{
			printf("exit\n");
			free_cmd (cmd);
			handle_ending(&suprem_knowledge);
			return (0);
		}
		if (str && str[0] != 0)
		{
			// free (str);
			// printf ("\"%s\"\n\n", str);
			str = input_with_space(str);
			suprem_knowledge->str = str;
			// free (str);
			// printf ("\"%s\"\n\n", str);
			// exit (EXIT_FAILURE);

		}
		if (quote_verif(str,&suprem_knowledge) != 0)
		{
			str++;
			add_history(str);
			free (suprem_knowledge->str);
			continue;
		}
		pipe_quota(str, &suprem_knowledge);
		if (cmd_nt_fd(str) != 0)
		{
			str++;
			add_history(str);
			free(suprem_knowledge->str);
			continue;
		}

		if (handle_readline(str, &suprem_knowledge, cmd) == 1)
		{
			break;
		}
		// free_cmd(cmd);
		// handle_cmd_list(suprem_knowledge->rl_tab);
		// handle_exec(suprem_knowledge);
		// rl_lst_clear(&token);

		free (str);
		str = NULL;
		// printf ("\"%s\"\n\n\n", str);

	// 	printf ("\n\n\n\n\n\n\n");

	// print_command_list(cmd);

	// 	printf ("\n\n\n\n\n\n\n");

	// print_tab(suprem_knowledge);

	// 	printf ("\n\n\n\n\n\n\n");
		printf ("g_sig : %d", g_sig);

		g_sig = 0;

	}
	handle_ending(&suprem_knowledge);
	return (0);
}
