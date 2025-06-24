/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:25:28 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/24 09:37:31 by qumiraud         ###   ########.fr       */
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
	g_status = 130;
}
void	signal_heredoc(int signal)
{
	(void)signal;
	g_status = 130;
	printf ("\n");
	close (0);
	return ;
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
	signal(SIGPIPE, SIG_IGN);
}
