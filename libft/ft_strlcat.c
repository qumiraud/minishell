/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:03:15 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 08:53:39 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	lendst;
	size_t	lensrc;

	if (!size)
		return (ft_strlen(src));
	len = ft_strlen(src) + ft_strlen(dst);
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (size < lendst)
		return (lensrc + size);
	while (lendst < len && lendst < size - 1)
	{
		dst[lendst] = *src;
		src++;
		lendst++;
	}
	dst[lendst] = 0;
	return (len);
}
