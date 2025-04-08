/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:10:39 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 09:41:03 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
	{
		return (0);
	}
	while (n -- && n > 0)
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
		}
	}
	return ((unsigned char) *str1 - (unsigned char) *str2);
}
