/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:22:26 by qumiraud          #+#    #+#             */
/*   Updated: 2025/02/10 10:46:09 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dup;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen((char *)s) - start)
		len = ft_strlen((char *)s) - start;
	dup = ft_calloc(len + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s + start, len);
	dup[len] = '\0';
	return (dup);
}
