/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:33:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/05/21 13:32:23 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	glt_copy_word(char *dest, char **src, int count_l)
{
	int	i;

	i = 0;
	while (**src && i != count_l)
	{
		*dest++ = **src;
		(*src)++;
		i++;
	}
	*dest = '\0';
	while (**src && ((**src >= 8 && **src <= 13) || **src == 32))
		src++;
}

void	fill_gluttony_tab(t_data **s_k, char *str)
{
	int	i;
	int	count_l;
	int	count_w;

	i = 0;
	(*s_k)->tab_len = 0;
	count_w = 0;
	count_w = glt_count_words(str);
	(*s_k)->glutto_tab = malloc(sizeof(char *) * (count_w + 1));
	while (str[0] == 32 || (str[0] >= 8 && str[0] <= 13))
		str++;
	while (str[0])
	{
		count_l = 0;
		count_l = glt_count_letters(str);
		(*s_k)->glutto_tab[i] = malloc(sizeof(char) * (count_l + 1));
		glt_copy_word((*s_k)->glutto_tab[i], &str, count_l);
		if (count_l)
			i++;
		while (*str && ((*str >= 8 && *str <= 13) || *str == 32))
			str++;
	}
	(*s_k)->glutto_tab[i] = NULL;
	(*s_k)->tab_len = i;
}
