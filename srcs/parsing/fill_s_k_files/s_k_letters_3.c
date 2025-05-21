/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_k_letters_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:52:31 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/21 13:31:56 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	double_redir_start(char *str, int i)
{
	if (i == 0 && ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<')))
	{
		return (i + 2);
	}
	return (0);
}

int	double_redir_middle(char *str, int i)
{
	if (i != 0 && ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<')))
	{
		return (i);
	}
	return (0);
}
