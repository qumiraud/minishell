/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glt_letters_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:29:14 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/10 09:58:42 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	fill_tabs(t_data **s_k, char *str)
{
	// fill_s_k_tab(s_k, str);
	fill_gluttony_tab(s_k, str);
}

int	handle_quotes_part2(char *str, int *i, int *quote, char c)
{
	while (str[*i])
	{
		if (str[*i] == 32 && (*quote % 2) == 0)
		{
			*quote = 0;
			return (1);
		}
		(*i)++;
		if (str[*i] == c)
			(*quote)++;
	}
	return (0);
}

int	handle_quotes(char *str, int *i, int *word)
{
	int		quote;
	char	c;

	quote = 1;
	c = str[*i];
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == c)
		{
			quote = 0;
			if (handle_quotes_part2(str, i, &quote, c))
				break ;
		}
		if (quote == 0)
		{
			(*word)++;
			if (*word == 1)
				return (*i);
			break ;
		}
	}
	return (0);
}

int	handle_double_redir(char *str, int i, int *inc)
{
	if ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
	{
		*inc = 2;
		return (1);
	}
	return (0);
}


int handle_single_redir(char *str, int i, int *inc) {
    if (str[i] == '>' || str[i] == '<' || str[i] == '|') {
        *inc = 1;
        return (1);
    }
    return (0);
}
