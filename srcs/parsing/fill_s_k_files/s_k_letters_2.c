/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_k_letters_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:44:17 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/21 13:25:19 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	single_redir_start(char *str, int i)
{
	if (i == 0 && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
	{
		return (i + 1);
	}
	return (0);
}

int	single_redir_middle(char *str, int i)
{
	if (i != 0 && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
	{
		return (i);
	}
	return (0);
}

int	quotes_part2(char *str, int *i, int *quote, char c)
{
	while (str[*i])
	{
		if (str[*i] == 32 && (*quote % 2) == 0)
		{
			*quote = 0;
			break ;
		}
		(*i)++;
		if (str[*i] == c)
			(*quote)++;
	}
	return (0);
}

int	quotes(char *str, int *i, int *word)
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
			quotes_part2(str, i, &quote, c);
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

int	redirections_part1(char *str, int i, int *inc)
{
	int	ret;

	ret = double_redir_start(str, i);
	if (ret > 0)
	{
		*inc = 2;
		return (ret);
	}
	ret = double_redir_middle(str, i);
	if (ret > 0)
	{
		*inc = 2;
		return (ret);
	}
	return (0);
}
