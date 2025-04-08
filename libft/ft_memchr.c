/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:16:29 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 08:49:32 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*itr;

	itr = (unsigned char *) s;
	while (n--)
	{
		if (*itr == (unsigned char)c)
			return (itr);
		itr++;
	}
	return (NULL);
}
