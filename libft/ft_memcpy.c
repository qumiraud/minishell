/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:17:58 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 09:57:15 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ndest;
	const char	*nsrc;

	ndest = dest;
	nsrc = src;
	if (ndest == NULL && nsrc == NULL)
		return (dest);
	while (n > 0)
	{
		*ndest = *nsrc;
		ndest++;
		nsrc++;
		n--;
	}
	return (dest);
}
