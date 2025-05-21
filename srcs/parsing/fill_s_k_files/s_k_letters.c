/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_k_letters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:44:19 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/21 13:33:48 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	redirections_part2(char *str, int i, int *inc)
{
	int	ret;

	ret = single_redir_start(str, i);
	if (ret > 0)
	{
		*inc = 1;
		return (ret);
	}
	ret = single_redir_middle(str, i);
	if (ret > 0)
	{
		*inc = 1;
		return (ret);
	}
	return (0);
}

int	redirections(char *str, int i, int *inc)
{
	int	ret;

	ret = redirections_part1(str, i, inc);
	if (ret > 0)
		return (ret);
	return (redirections_part2(str, i, inc));
}

int	process_redir(char *str, int *i, int ret, int inc)
{
	if (*i != 0 && (str[*i] == '>' || str[*i] == '<' || str[*i] == '|'
			|| (str[*i] == '>' && str[*i + 1] == '>')
			|| (str[*i] == '<' && str[*i + 1] == '<')))
	{
		*i += inc;
		return (ret);
	}
	*i += inc;
	return (ret);
}

int	process_word(char *str, int *i, int *word)
{
	int	ret;
	int	inc;

	while ((str[*i] && (str[*i] != 32 && (str[*i] <= 8 || str[*i] >= 13))))
	{
		ret = redirections(str, *i, &inc);
		if (ret > 0)
			return (process_redir(str, i, ret, inc));
		if (str[*i] == '\'' || str[*i] == '"')
		{
			ret = quotes(str, i, word);
			if (ret > 0)
				return (ret);
		}
		if (str[*i] != '\0')
			(*i)++;
	}
	return (0);
}

int	count_letters(char *str)
{
	int	i;
	int	word;
	int	result;

	i = 0;
	word = 0;
	while (str[i] && word == 0)
	{
		skip_spaces(str, &i);
		if (str[i] && (str[i] != 32 || (str[i] <= 8 || str[i] >= 13)))
		{
			if (word == 1)
				return (i);
			result = process_word(str, &i, &word);
			if (result > 0)
				return (result);
			word++;
		}
	}
	return (i);
}
