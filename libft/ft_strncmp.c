/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:45:51 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 09:36:15 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((unsigned char ) *s1
		&& (unsigned char ) *s1 == (unsigned char ) *s2 && n - 1)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}
