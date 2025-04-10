/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:53:00 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/10 16:13:35 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	count_words(char *str)
// {
// 	int	i;
// 	int	count;

// 	count = 1; ///str=" bonjour "
// 	i = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] == 32 || (str[i] >= 8 && str[i] <= 13)))
// 		{
// 			if (str[i - 1] > 32 && str[i + 1] != '\0')
// 			// if (str[i + 1] != '\0')

// 			count++;

// 		}
// 		printf ("\n\n\n%c : ", str[i]);
// 		printf("%d\n\n\n", count);
// 		i++;
// 	}
// 	printf("\n\n\n~~~countwords : %d~~~\n\n\n", count);
// 	return (count);
// }

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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

int	count_words(const char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str && str[i])
	{
		if ((str[i] != 32) && !(str[i] >= 8 && str[i] <= 13))
		{
			word++;
			while (((str[i] != 32) && !(str[i] >= 8 && str[i] <= 13)) && str[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}
