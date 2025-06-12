/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glt_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:29:55 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/12 10:19:45 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_quotes_part2_w(const char *str, int *i, int *quote, char c)
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

void	handle_quotes_w(const char *str, int *i, int *word, int *quote)
{
	char	c;

	*quote = 1;
	c = str[*i];
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == c)
		{
			handle_quotes_part2_w(str, i, quote, c);
		}
		if (*quote == 0)
		{
			(*word)++;
			break ;
		}
	}
}

void	handle_redirections_w(const char *str, int *i, int *word)
{
	handle_double_redir_w(str, i, word);
	handle_single_redir_no_space(str, i, word);
	handle_single_redir_partial_space_1(str, i, word);
	handle_single_redir_partial_space_2(str, i, word);
}

void	process_word_w(const char *str, int *i, int *word, int *quote)
{
	while ((str[*i] && (str[*i] != 32 && (str[*i] <= 8 || str[*i] >= 13))))
	{
		handle_redirections_w(str, i, word);
		if (str[*i] == '\'' || str[*i] == '"')
			handle_quotes_w(str, i, word, quote);
		if (str[*i] != '\0')
			(*i)++;
	}
}

int	glt_count_words(const char *str)
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
	printf ("WORD : %d\n\n\n", word);
	return (word);
}
