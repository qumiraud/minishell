/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:33:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/20 09:46:00 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_quote_case(char *dest, char **src, char *quote)
{
	if ((**src == '\'' || **src == '"') && *quote == 0)
	{
		*quote = **src;
		while (**src)
		{
			if (**src == *quote)
			{
				(*src)++;
				break ;
			}
			*dest++ = **src;
			(*src)++;
		}
		*quote = 0;
		return (1);
	}
	return (0);
}

int	should_continue_copying(char **src)
{
	static int	quote;

	if (!**src)
		return (0);
	if ((**src == '\'' || **src == '"') && quote == 1)
	{
		quote = 0;
	}
	else if (**src == '\'' || **src == '"')
		quote = 1;
	if ((**src == ' ' || (**src >= 9 && **src <= 13)) && quote == 0)
		return (0);
	if (is_operator(**src))
		return (0);
	return (1);
}

void	glt_copy_word(char *dest, char **src, int count_l)
{
	char	quote;
	char	*dest_start;
	int		i;

	i = 0;
	quote = 0;
	dest_start = dest;
	skip_whitespace(src);
	while (should_continue_copying(src) && i != count_l)
	{
		i++;
		if (!handle_quote_case(dest_start, src, &quote))
		{
			*dest_start++ = **src;
			(*src)++;
		}
	}
	*dest_start = '\0';
	skip_whitespace(src);
}

void	handle_standard_token(t_data **s_k, char **str, int *i)
{
	int	len;

	len = glt_count_letters(*str);
	if (len > 0)
	{
		(*s_k)->glutto_tab[*i] = malloc(len + 1);
		glt_copy_word((*s_k)->glutto_tab[*i], str, len);
		(*i)++;
	}
}

int	allocate_glutto_tab(t_data **s_k, char *str)
{
	(*s_k)->glutto_tab = malloc(sizeof(char *)
			* (glt_count_words(str) + (*s_k)->pipe_quo + 2));
	if (!(*s_k)->glutto_tab)
		return (0);
	return (1);
}
