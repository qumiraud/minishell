/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_suprem_knowledge.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:40:08 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/07 14:59:43 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	fill_s_k_ws_lst(t_data **s_k)
// {



// }

void	fill_s_k_tab(t_data **s_k, char *str)
{
	int	i;
	int	j;
	int	count;
	char *nav;
	int	k = 0;
	int nb_words;

	nb_words = count_words(str);
	i = 0;
	j = 0;
	nav = str;

	(*s_k)->rl_tab = malloc(sizeof(char *) * (nb_words + 1));
	while (1)
	{
		if (str[0] == '\0')
			break ;
		count = 0;
		while (nav[k] && (((nav[k]) <= 8 || (nav[k]) >= 13) && nav[k] != 32))
		{
			if ((nav[k]) == '\'' || (nav[k]) == '"')
				k++;
			// else if ( nav[k] > 32 && (((nav[k]) >= 8 && (nav[k]) <= 13) || nav[k] == 32))
			// {
			// 	// count++;
			// 	k++;
			// 	break ;
			// }
			k++;
			count++;
		}

		printf("\n\n\n\n %d \n\n\n\n", count);

		(*s_k)->rl_tab[i] = malloc(sizeof(char) * (count + 1));
		while (*str)
		{
			if ((*str) == '\'' || (*str) == '"')
				str++;
			if (((*str) >= 8 && (*str) <= 13) || *str == 32)
			{
				str++;
				(*s_k)->rl_tab[i][j] = '\0';
				// i++;
				// printf("\n\n\n\n i : %d \n\n\n\n", i);
				// printf("\n\nCOUCOU\n\n");
				break ;
			}
			(*s_k)->rl_tab[i][j] = *str;
			printf("\n----------\n (*s_k)->rl_tab[i][j] : %c & *str : %c & i : %d\n------------\n", (*s_k)->rl_tab[i][j], (*str), i);
			str++;
			j++;
		}
		j = 0;
		printf("\n\n\n\n %s \n\n\n\n", (*s_k)->rl_tab[i]);
		i++;
		k++;
		printf("\n|||||||||||||\ncount : %d & nb_words : %d \n|||||||||||||\n ", count, nb_words);
	}
	(*s_k)->rl_tab[i] = NULL;
}

void	fill_suprem_knowledge(t_data **s_k, char *str)
{
	if (!s_k || !(*s_k))
		return ;
	fill_s_k_tab(s_k, str);
	// fill_s_k_ws_lst(s_k);
}

void free_data(t_data **s_k)
{
	int	i;

	i = 0;
	while (i < (*s_k)->tab_len)
		free((*s_k)->rl_tab[i]);
	free((*s_k)->rl_tab);
	free(*s_k);
}

void	init_suprem_knowledge(t_data **s_k)
{
	int	len;

	len = 0;
	(*s_k) = malloc(sizeof(t_data));
	if (!s_k)
	{
		printf("mince alors\n");
		return ;
	}
	(*s_k)->rl_tab = NULL;
	(*s_k)->tab_len = 0;
}
