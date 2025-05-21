/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:56:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/21 15:56:04 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	char	*str1;
	char	*str2;
	char	*start;

	if (!s1 || !s2)
		return (NULL);
	str1 = (char *) s1;
	str2 = (char *) s2;
	s3 = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	start = s3;
	while (*str1)
	{
		*s3 = *str1;
		s3++;
		str1++;
	}
	while (*str2)
	{
		*s3 = *str2;
		s3++;
		str2++;
	}
	*s3 = '\0';
	return (start);
}
