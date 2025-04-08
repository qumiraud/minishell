/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:05:58 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 08:57:59 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ndest;
	const char	*nsrc;

	ndest = dest;
	nsrc = src;
	if (!n)
		return (dest);
	if (ndest == NULL && nsrc == NULL)
		return (dest);
	if (ndest < nsrc)
		return (ft_memcpy(ndest, src, n));
	else
	{
		while (n > 0)
		{
			ndest[n - 1] = nsrc[n - 1];
			n--;
		}
		return (dest);
	}
}
