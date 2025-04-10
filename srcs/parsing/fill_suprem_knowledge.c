/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_suprem_knowledge.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:40:08 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/10 12:25:33 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	fill_s_k_ws_lst(t_data **s_k)
// {

// }

void	copy_word(char *dest, char **src)
{
	while (**src && !((**src >= 8 && **src <= 13) || **src == 32))
	{
		if (**src != '"' && **src != '\'')
			*dest++ = **src;
		(*src)++;
	}
	*dest = '\0';
}

int	ref_fill_s_k_tab(int k, int count, char *str)
{
	while (str[k] && (str[k] > 13 || str[k] < 8) && str[k] != 32)
	{
		if (str[k] != '"' && str[k] != '\'')
			count++;
		k++;
	}
	return (count);
}

void	fill_s_k_tab(t_data **s_k, char *str)
{
	int	i;
	int	k;
	int	count;

	i = 0;
	(*s_k)->tab_len = 0;
	(*s_k)->rl_tab = malloc(sizeof(char *) * (count_words(str) + 1));
	while (str[0] && str[0] != '"' && str[0] != '\'')
	{
		count = 0;
		k = 0;
		count = ref_fill_s_k_tab(k, count, str);
		(*s_k)->rl_tab[i] = malloc(sizeof(char) * (count + 1));
		copy_word((*s_k)->rl_tab[i], &str);
		if (count)
			i++;
		while (*str && ((*str >= 8 && *str <= 13) || *str == 32))
			str++;
	}
	(*s_k)->rl_tab[i] = NULL;
	(*s_k)->tab_len = i;
}

void	fill_suprem_knowledge(t_data **s_k, char *str)
{
	if (!s_k || !(*s_k))
		return ;
	fill_s_k_tab(s_k, str);
}

void	free_data(t_data **s_k)
{
	int	i;
	t_data	*data = *s_k;

	i = 0;
	if ((*s_k)->rl_tab)
	{
		while (i <= (*s_k)->tab_len)
		{
			free((*s_k)->rl_tab[i]);
			i++;
		}
		(*s_k)->tab_len = 0;
	}
	if (data->rl_tab)
		free(data->rl_tab);
}

void	init_suprem_knowledge(t_data **s_k)
{
	(*s_k) = malloc(sizeof(t_data));
	if (!s_k)
	{
		printf("mince alors\n");
		return ;
	}
	(*s_k)->rl_tab = NULL;
	(*s_k)->tab_len = 0;
}
