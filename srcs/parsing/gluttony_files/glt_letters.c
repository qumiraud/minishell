/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glt_letters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeten <yeten@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:27:20 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/11 18:31:19 by yeten            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_redirections(char *str, int i, int *inc)
{
	*inc = 0;
	if (i == 0)
	{
		if (handle_double_redir(str, i, inc))
			return (i + *inc);
		if (handle_single_redir(str, i, inc))
			return (i + *inc);
	}
	else
	{
		if (handle_double_redir(str, i, inc))
			return (i);
		if (handle_single_redir(str, i, inc))
			return (i);
	}
	return (0);
}

int	process_word_part2(char *str, int *i, int *word, int redir_pos)
{
	int	inc;

	if (redir_pos > 0)
	{
		if (*i != 0 && (str[*i] == '>' || str[*i] == '<' || str[*i] == '|'
				|| (str[*i] == '>' && str[*i + 1] == '>')
				|| (str[*i] == '<' && str[*i + 1] == '<')))
		{
			*word = redir_pos;
			handle_redirections(str, *i, &inc);
			*i += inc;
			return (*word);
		}
		return (redir_pos);
	}
	return (0);
}

int	glt_process_word(char *str, int *i, int *word)
{
	int	redir_pos;
	int	result;
	int	inc;

	while ((str[*i] && (str[*i] != 32 && (str[*i] <= 8 || str[*i] >= 13))))
	{
		redir_pos = handle_redirections(str, *i, &inc);
		result = process_word_part2(str, i, word, redir_pos);
		if (result > 0)
			return (result);
		if (str[*i] == '\'' || str[*i] == '"')
			return (handle_quotes(str, i, word));
		if (str[*i] != '\0')
			(*i)++;
	}
	return (0);
}

void	skip_spaces(char *str, int *i)
{
	printf ("HALLO????\n\n\n\n");
	while (str[*i] == 32 || (str[*i] >= 8 && str[*i] <= 13))
		(*i)++;
}

int	glt_count_letters(char *str)
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
			result = glt_process_word(str, &i, &word);
			if (result > 0)
				return (result);
			word++;
		}
	}
	return (i);
}
