/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:25:28 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/12 10:24:24 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// void sig_pipe_handler(int signal)
// {
// 	(void)signal;
// 	write(2, "test bonjou\n\n", 13);
// 	printf ("HALLLLLOOOO>?????\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
// 		g_sig = 1;
// }

void	setup_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGPIPE, signal_handler);
	signal(SIGPIPE, SIG_IGN);
}
