/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:25:28 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/15 11:49:05 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0); // temporaire ca doit rien ecrire ca juste des guillemets !!!!
	rl_on_new_line();
	rl_redisplay();	
}


void	setup_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);	
}
















