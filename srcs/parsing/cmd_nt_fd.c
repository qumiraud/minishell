/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nt_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:11:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/06 08:55:58 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	cmd_nt_fd(char *str) //, t_data **s_k)
{
	// besoin de plus de test pour pas faire de la merde 24/04/2025
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		i++;
	// if (str[i] == '$')
		// return (printf("$: command not found\n"));
	if (str[i] == '|' && str[i + 1] == '|')
		return (printf("bash: syntax error near unexpected token `||'\n"));
	else if (str[i] == '|')
		return (printf("bash: syntax error near unexpected token `|'\n"));
	// else if (str[i] == '' && str[i + 1] == '>')
		// return (printf("bash: syntax error near unexpected token `newline'\n"));
	// else if (str[i] == '>' && str[i + 1] == '<')
		// return (printf("bash: syntax error near unexpected token `<'\n"));
	// else if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '<'))
		// return (printf("bash: syntax error near unexpected token `newline'\n"));
	// else if (str[i] == '<' || str[i] == '>')
		// return (printf("bash: syntax error near unexpected token `newline'\n"));

	return (0);
}