/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:25:49 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 10:28:04 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		j;
	size_t	nlen;

	if ((!big || !little) && len == 0)
		return (NULL);
	if (little[0] == '\0')
		return ((char *) big);
	i = 0;
	while (big[i] && len > 0)
	{
		j = 0;
		nlen = len;
		while (big[i + j] == little[j] && nlen)
		{
			if ((little[j + 1]) == '\0')
				return ((char *)big + i);
			j++;
			nlen--;
		}
		i++;
		len--;
	}
	return (NULL);
}
