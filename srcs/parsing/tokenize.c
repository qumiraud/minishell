/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:24 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/10 15:32:56 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if ((c >= 8 && c <= 13) || c == 32)
	{
		return (0);
	}
	return (1);
}

void	tokenize(char *str, t_lst_arg **token)
{
	char	quote;
	char	*start;
	int		i;

	quote = 0;		//" echo "bonjour" > text.txt | cat -e < text.txt
	i = 0;
	start = NULL;
	while (*str)
	{
		if (quote)
		{
			if (*str == quote || *str == quote)
			{
				rl_lst_addback(token, rl_lst_new(start, str, i));
				quote = 0;
				start = NULL;
				(*token)->type = QUOTES;
				i++;
			}
		}
		else if (*str == '\'' || *str == '"')
		{
			if (start)
				rl_lst_addback(token, rl_lst_new(start, str, i));
			quote = *str;
			start = str + 1;
		}
		else if (is_whitespace(*str) == 0)
		{
			if (start)
			{
				rl_lst_addback(token, rl_lst_new(start, str + 1, i));
				i++;
				start = NULL;
			}
		}
		else if (ft_strchr("><|", *str))
		{
			if (start)
			{
				rl_lst_addback(token, rl_lst_new(start, str, i));
				i++;
				start = NULL;
			}
			if (*(str + 1) == '>' && *str == '>' )
			{
				rl_lst_addback(token, rl_lst_new(start, str, i));
				i++;
				str++;
				(*token)->type = APPEND;
			}
			else
			{
				rl_lst_addback(token, rl_lst_new(start, str, i));
				i++;
				(*token)->type = OPERATORS;
			}
		}
		else
		{
			if (!start)
				start = str;
		}
		str++;
	}
	if (start)
	{
		rl_lst_addback(token, rl_lst_new(start, str, i));
		i++;
	}
	// nav = (*token);
	// while (nav)
	// {
	// 	printf("~%s~\n\n", nav->rl_arg);
	// 	nav = nav->next;
	// }
}
