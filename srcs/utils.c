/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:53:00 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/07 14:35:27 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	count_words(const char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str && str[i])
	{
		if (str[i] != 32 || (str[i] >= 8 && str[i] <= 13))
		{
			word++;
			while ((str[i] != 32 || (str[i] >= 8 && str[i] <= 13)) && str[i])
				i++;
			printf ("\n\n\n%c : ", str[i]);
			printf("%d\n\n\n", word);
		}
		else
			i++;
	}
	printf("\n\n\n~~~countwords : %d~~~\n\n\n", word);
	return (word);
}