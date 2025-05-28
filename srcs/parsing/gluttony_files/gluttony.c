/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:33:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/26 15:23:23 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	glt_copy_word(char *dest, char **src/*, int count_l*/)
{
	char quote;

	quote = 0;
	while (**src == ' ' || (**src >= 9 && **src <= 13))
		(*src)++;
	while (**src && (**src != ' ' && !(**src >= 9 && **src <= 13)))
	{

		if ((**src == '\'' || **src == '"') && quote == 0)
		{
			quote = **src;
			(*src)++;
			while (**src && **src != quote)
			{
				*dest++ = **src;
				(*src)++;
			}
			if (**src == quote)
			{
				(*src)++;
				quote = 0;
			}
		}
		else
		{
			*dest++ = **src;
			(*src)++;
		}
	}
	*dest = '\0';
	while (**src == ' ' || (**src >= 9 && **src <= 13))
		(*src)++;
}

void	fill_gluttony_tab(t_data **s_k, char *str)
{
	int i = 0;
	int count_w = glt_count_words(str);

	(*s_k)->glutto_tab = malloc(sizeof(char *) * (count_w + 1));

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;

	while (*str)
	{
		(*s_k)->glutto_tab[i] = malloc(sizeof(char) * (strlen(str) + 1));

		glt_copy_word((*s_k)->glutto_tab[i], &str);

		if (*((*s_k)->glutto_tab[i]))
			i++;

		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
	}
	(*s_k)->glutto_tab[i] = NULL;
	(*s_k)->tab_len = i;
}
