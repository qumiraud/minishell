/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_k_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:44:24 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/21 13:31:39 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	quotes_part2_w(const char *str, int *i, int *quote, char c)
{
	int	quotes;

	quotes = 0;
	while (str[*i])
	{
		if (str[*i] == 32 && (quotes % 2) == 0)
		{
			*quote = 0;
			break ;
		}
		(*i)++;
		if (str[*i] == c)
			quotes++;
	}
}

void	quotes_w(const char *str, int *i, int *word, int *quote)
{
	char	c;

	*quote = 1;
	c = str[*i];
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == c)
		{
			quotes_part2_w(str, i, quote, c);
		}
		if (*quote == 0)
		{
			(*word)++;
			break ;
		}
	}
}

void	redirections_w(const char *str, int *i, int *word)
{
	double_redir_w(str, i, word);
	single_redir_no_space(str, i, word);
	single_redir_partial_space_1(str, i, word);
	single_redir_partial_space_2(str, i, word);
}

int	count_words(const char *str)
{
	int	i;
	int	word;
	int	quote;

	i = 0;
	word = 0;
	quote = 0;
	while (str[i])
	{
		skip_spaces_w(str, &i);
		if (str[i] && (str[i] != 32 || (str[i] <= 8 || str[i] >= 13)))
		{
			word++;
			quote = 0;
			process_word_w(str, &i, &word, &quote);
		}
	}
	return (word);
}
