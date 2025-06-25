/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:20:15 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/25 13:39:01 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtrim(char const *s1, char const *set)
{
	size_t start;
	size_t end;
	size_t len;

	if (!s1 || !set)
		return (NULL);

	len = ft_strlen(s1);
	start = 0;
	end = len;

	// Trouver le début réel
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;

	// Trouver la fin réelle
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;

	return (ft_substr(s1, start, end - start));
}

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	int		i;
// 	int		k;
// 	int		j;

// 	i = 0;
// 	k = 0;
// 	if (!s1 || !set)
// 		return (NULL);
// 	j = ft_strlen((char *) s1);
// 	while (set[k])
// 	{
// 		if (s1[i] == set[k])
// 		{
// 			i++;
// 			k = 0;
// 		}
// 		else if (s1[j] == set[k])
// 		{
// 			j--;
// 			k = 0;
// 		}
// 		else
// 			k++;
// 	}
// 	return (ft_substr(s1, i, j - i + 1));
// }
