/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/21 16:25:40 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void free_cmd(t_cmd *cmd)
{
	// tres problemes ca need correctifs asap
	t_cmd *tmp;
	int i;

	i = 0;
	while (cmd)
	{

		// probleme sur des awd > awd > awd et aussi des awd | awd toi fatigue toi trouver quand energie plus


		tmp = cmd->next;
		// printf ("cmd->argc : %d\n", cmd->argc);
		// printf ("cmd->nb_ope : %d\n", cmd->nb_ope);


			while (i < (cmd->argc))//+ cmd->nb_ope))
			{

				// printf ("\n\n\nHALLO???\n\n\n");
				free(cmd->args[i]);
				cmd->args[i] = NULL;
				i++;
			//} <- while

				if (cmd->input_file)
				{
					free(cmd->input_file);
					cmd->input_file = NULL;
				}
				if (cmd->output_file)
				{
					free(cmd->output_file);
					cmd->output_file = NULL;
				}
			}
			i = 0;



		free(cmd);
		cmd = tmp;


	}
}






void	handle_str(char *str, t_data **s_k, t_lst_arg **token, t_cmd *cmd)
{
	str++; // verifier que ca ne pose pas de probleme c'est pour supprimer l'espace rajouter, pour qu'il ne soit pas dans le add history
	add_history(str);
	// tokenize(str, token);
	// (*s_k)->rl_lst = (*token);
	(void)token;
	fill_suprem_knowledge(s_k, str);
	// tokenize(s_k, token);
	// (*s_k)->cmd_arg = (*token);
	// re_token_wd(s_k);

	//t_cmd *
	cmd = parse_cmd((*s_k)->rl_tab);



	// printf ("\npipe_quo : %d\n", (*s_k)->pipe_quo);



	//  print_command_list(cmd);


	// print_tab(*s_k);
	// free (str);
	// str = NULL;
	// printf ("\"%s\"\n\n\n", str);

	// printf ("HALLO\n\n\n");


	handle_exec(*s_k, cmd);
	
	
	
	printf ("HALLO\n\n\n");

	free_cmd(cmd);
	// free (str);
	// str = NULL;

	// print_command_list(cmd);

	// free (cmd); // non pas la ???
}

void	handle_ending(t_data **s_k, t_lst_arg **token)
{
	free_data(s_k);
	free(*s_k);
	(*s_k) = NULL;
	rl_lst_clear(token);
	// printf ("HALLO\n\n\n");
	printf("exit\n");

}

int	handle_readline(char *str, t_data **s_k, t_lst_arg **token, t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (*str)
		handle_str(str, s_k, token, cmd);
	


	// free_cmd(cmd);

	free (str);
	str = NULL;
		// if ((*s_k)->rl_tab != NULL && !(ft_strncmp((*s_k)->rl_tab[0], "exit", 4)))
	// if ((*token) != NULL && !(ft_strncmp((*token)->rl_arg, "exit", 4)))
	// {
	// 	free (str);
	// 	str = NULL;
	// 	return (1);
	// }
	len = (*s_k)->tab_len;
	if (*s_k)
	{
		if ((*s_k)->rl_tab)
		{
			while (i <= len)
			{
				free((*s_k)->rl_tab[i]);
				(*s_k)->rl_tab[i] = NULL;
				i++;
			}
			i = 0;
		}
		if ((*s_k)->glutto_tab)
		{
			while (i <= len)
			{
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
	free (str);
	str = NULL;
	// print_command_list(*cmd);


	// if (cmd)
	// {
	// 	printf ("\n\n\nHALLO???\n\n\n");
	// 	// if (cmd->args[cmd->argc])
	// 	// {
	// 	// 	while (cmd->args[cmd->argc])
	// 	// 	{
	// 	// 		free (cmd->args[cmd->argc]);
	// 	// 		cmd->args[cmd->argc] = NULL;
	// 	// 		cmd->args[cmd->argc++];
	// 	// 	}


	// 	// }



	// 	free (cmd);
	// }



	return (0);
}

// void	handle_cmd_list(char **token)
// {
// 	// parse_cmd(token);

// 	// print_command_list(cmd);




// }

char *input_with_space(char *str)
{
	int len;
	char *new_str;

	new_str = NULL;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = ft_strjoin(" ", str);
	if (!new_str)
		return (NULL);
	// new_str[0] = ' ';
	// ft_strcpy(str, new_str + 1);
	free (str);
	str = NULL;
	// printf ("%s\n\n", new_str);
	return (new_str);
}





int	main(int argc, char **argv, char **envp)
{
	t_data		*suprem_knowledge;
	t_lst_arg	*token;
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
	token = NULL;
	while (1)
	{
		setup_signal();
		str = readline("💾 minishell :");
		printf ("%s\n\n", str);
		if (ft_strcmp(str, "exit") == 1)
		{
			free (str);
			str = NULL;
			handle_ending(&suprem_knowledge, &token);

			return (0);
		}
		if (!str)
		{
			printf("exit\n");
			free_cmd (cmd);
			handle_ending(&suprem_knowledge, &token);
			return (0);
		}
		if (str && str[0] != 0)
		{
			// free (str);
			// printf ("\"%s\"\n\n", str);
			str = input_with_space(str);
			// free (str);
			// printf ("\"%s\"\n\n", str);
			// exit (EXIT_FAILURE);
			
		}
		if (quote_verif(str,&suprem_knowledge) != 0)
		{
			str++;
			add_history(str);
			// free (str);
			continue;
		}
		pipe_quota(str, &suprem_knowledge);
		// if (cmd_nt_fd(str) != 0)
		// {
		// 	add_history(str);
		// 	continue;
		// }
		// if (ft_strncmp(str, " CLEAR", 5) == 0 || ft_strncmp(str, " clear", 5) == 0)
		// {
		// 	add_history(str);
		// 	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		// 	continue;
		// }

		if (handle_readline(str, &suprem_knowledge, &token, cmd) == 1)
			break;
		// free_cmd (cmd);
		// handle_cmd_list(suprem_knowledge->rl_tab);
		// handle_exec(suprem_knowledge);
		rl_lst_clear(&token);

		// free (str);
		// str = NULL;
		// printf ("\"%s\"\n\n\n", str);

	}
	handle_ending(&suprem_knowledge, &token);
	return (0);
}
