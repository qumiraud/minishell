/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/19 15:47:21 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"








// void exec_command(t_cmd *cmd)
// {
//     pid_t pid = fork();  // Crée un processus fils

//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid == 0)  // Processus fils
//     {
//         // Gérer les redirections de fichiers (si présentes)
//         if (cmd->input_file)
//         {
//             int in_fd = open(cmd->input_file, O_RDONLY);
//             if (in_fd == -1)
//             {
//                 perror("open input file");
//                 exit(EXIT_FAILURE);
//             }
//             if (dup2(in_fd, STDIN_FILENO) == -1)
//             {
//                 perror("dup2 input file");
//                 close(in_fd);
//                 exit(EXIT_FAILURE);
//             }
//             close(in_fd);
//         }

//         if (cmd->output_file)
//         {
//             int out_fd;
//             if (cmd->append)  // Si l'option 'append' est activée
//                 out_fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//             else  // Si l'option 'append' n'est pas activée
//                 out_fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

//             if (out_fd == -1)
//             {
//                 perror("open output file");
//                 exit(EXIT_FAILURE);
//             }
//             if (dup2(out_fd, STDOUT_FILENO) == -1)
//             {
//                 perror("dup2 output file");
//                 close(out_fd);
//                 exit(EXIT_FAILURE);
//             }
//             close(out_fd);
//         }

//         // Préparer les arguments pour execvp
//         char *args[cmd->argc + 1];
//         for (int i = 0; i < cmd->argc; i++)
//         {
//             args[i] = cmd->args[i];
//         }
//         args[cmd->argc] = NULL;  // Terminator pour execvp

//         // Exécuter la commande
//         if (execvp(args[0], args) == -1)
//         {
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else  // Processus parent
//     {
//         int status;
//         waitpid(pid, &status, 0);  // Attendre que le processus fils termine
//         if (WIFEXITED(status))
//         {
//             printf("Le processus fils a terminé avec le code de sortie %d\n", WEXITSTATUS(status));
//         }
//         else
//         {
//             printf("Le processus fils a échoué\n");
//         }
//     }
// }









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
	add_history(str);
	tokenize(str, token);
	// (*s_k)->rl_lst = (*token);
	fill_suprem_knowledge(s_k, str);
	// tokenize(s_k, token);
	// (*s_k)->cmd_arg = (*token);
	// re_token_wd(s_k);

	//t_cmd *
	cmd = parse_cmd((*s_k)->rl_tab);



	// printf ("\npipe_quo : %d\n", (*s_k)->pipe_quo);



	 print_command_list(cmd);

	// exec_command(cmd);

	// print_tab(*s_k);

	handle_exec(*s_k, cmd); //

	// printf ("HALLO\n\n\n");

	free_cmd(cmd);

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
	if ((*token) != NULL && !(ft_strncmp((*token)->rl_arg, "exit", 4)))
	{
		free(str);
		str = NULL;
		return (1);
	}
	len = (*s_k)->tab_len;
	if (*str)
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
		if (!str)
		{
			printf("exit\n");
			handle_ending(&suprem_knowledge, &token);
			return (0);
		}
		if (quote_verif(str,&suprem_knowledge) != 0)
		{
			add_history(str);
			continue;
		}
		pipe_quota(str, &suprem_knowledge);
		if (cmd_nt_fd(str) != 0)
		{
			add_history(str);
			continue;
		}
		if (ft_strncmp(str, "CLEAR", 5) == 0 || ft_strncmp(str, "clear", 5) == 0)
		{
			add_history(str);
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			continue;
		}

		if (handle_readline(str, &suprem_knowledge, &token, cmd) == 1)
			break;
		// handle_cmd_list(suprem_knowledge->rl_tab);
		// handle_exec(suprem_knowledge);
		rl_lst_clear(&token);
		free (str);
		str = NULL;
	}
	handle_ending(&suprem_knowledge, &token);
	return (0);
}
