/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_k_words_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:44:22 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/21 13:35:19 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	double_redir_w(const char *str, int *i, int *word)
{
	if ((str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '<' && str[*i + 1] == '<'))
	{
		if (str[*i + 2] == ' ' || (str[*i - 1] != ' ' && str[*i + 2] != ' '))
			*word += 2;
		else
			(*word)++;
		if ((str[*i - 1] == ' ' && str[*i + 2] == ' '))
			(*word)--;
		*i += 2;
	}
}

void	single_redir_no_space(const char *str, int *i, int *word)
{
	if ((str[*i] == '>' && str[*i - 1] != ' ' && str[*i + 1] != ' ')
		|| (str[*i] == '<' && str[*i - 1] != ' ' && str[*i + 1] != ' ')
		|| (str[*i] == '|' && str[*i - 1] != ' ' && str[*i + 1] != ' '))
	{
		*word += 2;
	}
}

void	single_redir_partial_space_1(const char *str, int *i, int *word)
{
	if ((str[*i] == '>' && str[*i - 1] == ' ' && str[*i + 1] != ' ')
		|| (str[*i] == '>' && str[*i - 1] != ' ' && str[*i + 1] == ' ')
		|| (str[*i] == '<' && str[*i - 1] == ' ' && str[*i + 1] != ' '))
	{
		(*word)++;
	}
}

void	single_redir_partial_space_2(const char *str, int *i, int *word)
{
	if ((str[*i] == '<' && str[*i - 1] != ' ' && str[*i + 1] == ' ')
		|| (str[*i] == '|' && str[*i - 1] == ' ' && str[*i + 1] != ' ')
		|| (str[*i] == '|' && str[*i - 1] != ' ' && str[*i + 1] == ' '))
	{
		(*word)++;
	}
}
