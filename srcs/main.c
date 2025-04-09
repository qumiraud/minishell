/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/08 14:55:30 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void handle_sigint(int signum)
{
	if (signum == 2)
		printf("\n💾 minishell :");
	// if

}


int	main(void)
{
	t_data		*suprem_knowledge;
	t_lst_arg	*token;
	char		*str;

	init_suprem_knowledge(&suprem_knowledge);
	if (!suprem_knowledge)
		return (printf("mince alors\n"));
	token = NULL;
	while ((str = readline("💾 minishell :")) != NULL)
	{
		if (*str)
		{
			add_history(str);
			tokenize(str, &token);
			suprem_knowledge->rl_lst = token;
			fill_suprem_knowledge(&suprem_knowledge, str);
		}
		if (token != NULL && !(strcmp(token->rl_arg, "exit")))
		{
			free(str);
			break;
		}

		// while (suprem_knowledge->rl_lst->next)
		// {
		// 	printf("token %d : %s\n", suprem_knowledge->rl_lst->index, suprem_knowledge->rl_lst->rl_arg);
		// 	suprem_knowledge->rl_lst = suprem_knowledge->rl_lst->next;
		// }
		// printf("fin : token %d : %s\n", suprem_knowledge->rl_lst->index, suprem_knowledge->rl_lst->rl_arg);
		// sleep (1);
		// while (suprem_knowledge->rl_lst->prev)
		// {
		// 	printf("retour\n");
		// 	printf("token %d : %s\n", suprem_knowledge->rl_lst->index, suprem_knowledge->rl_lst->rl_arg);
		// 	suprem_knowledge->rl_lst = suprem_knowledge->rl_lst->prev;
		// }
		if (*str)
			free_data(&suprem_knowledge);
		rl_lst_clear(&token);
		free (str);
	}
	free_data(&suprem_knowledge);
	free(suprem_knowledge);
	rl_lst_clear(&token);
	printf("exit\n");
	return (0);
}