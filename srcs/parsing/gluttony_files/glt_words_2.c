/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glt_words_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:30:06 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/03 17:42:23 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	skip_spaces_w(const char *str, int *i)
{
	while (str[*i] == 32 || (str[*i] >= 8 && str[*i] <= 13))
		(*i)++;
}

void	handle_double_redir_w(const char *str, int *i, int *word)
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

void	handle_single_redir_no_space(const char *str, int *i, int *word)
{
	if ((str[*i] == '>' && str[*i - 1] != ' ' && str[*i + 1] != ' ')
		|| (str[*i] == '<' && str[*i - 1] != ' ' && str[*i + 1] != ' ')
		|| (str[*i] == '|' && str[*i - 1] != ' ' && str[*i + 1] != ' '))
	{
		*word += 2;
	}
}

void	handle_single_redir_partial_space_1(const char *str, int *i, int *word)
{
	if ((str[*i] == '>' && str[*i - 1] == ' ' && str[*i + 1] != ' ')
		|| (str[*i] == '>' && str[*i - 1] != ' ' && str[*i + 1] == ' ')
		|| (str[*i] == '<' && str[*i - 1] == ' ' && str[*i + 1] != ' '))
	{
		(*word)++;
	}
}

void handle_single_redir_partial_space_2(const char *str, int *i, int *word) {
    if (str[*i] == '|') {
        if (str[*i - 1] != ' ' || str[*i + 1] != ' ') {
            (*word)++;
        }
        (*i)++;
    }
}

