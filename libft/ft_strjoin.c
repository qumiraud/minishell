/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:56:04 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 09:36:55 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	char	*str1;
	char	*str2;

	if (!s1 || !s2)
		return (NULL);
	str1 = (char *) s1;
	str2 = (char *) s2;
	s3 = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
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
	return (s3 - (ft_strlen(s1) + ft_strlen(s2)));
}
