/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/10 16:20:53 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void handle_sigint(int signum)
{
	if (signum == 2)
		printf("\n💾 minishell :");
	// if

}

void	handle_str(char *str, t_data **s_k, t_lst_arg **token)
{
	add_history(str);
	tokenize(str, token);
	(*s_k)->rl_lst = (*token);
	fill_suprem_knowledge(s_k, str);
}

void	handle_ending(t_data **s_k, t_lst_arg **token)
{
	free_data(s_k);
	free(*s_k);
	rl_lst_clear(token);
	printf("exit\n");
}

int	handle_readline(char *str, t_data **s_k, t_lst_arg **token)
{
	if (*str)
			handle_str(str, s_k, token);
	if ((*token) != NULL && !(strcmp((*token)->rl_arg, "exit")))
	{
		free(str);
		return (1);
	}
	if (*str)
		free_data(s_k);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*suprem_knowledge;
	t_lst_arg	*token;
	char		*str;

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
		str = readline("💾 minishell :");
		if (handle_readline(str, &suprem_knowledge, &token) == 1)
			break;
		rl_lst_clear(&token);
		free (str);
	}
	handle_ending(&suprem_knowledge, &token);
	return (0);
}