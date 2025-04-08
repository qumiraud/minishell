/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:48:41 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 09:34:46 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *) s;
	while (s[i])
		i++;
	if ((unsigned char) c == '\0')
	{
		while (*str)
			str++;
		return (str);
	}
	while (s[i - 1] && i >= 0)
	{
		if (s[i - 1] == (unsigned char) c)
			return ((char *) s + i - 1);
		i--;
	}
	if (*s == 0 && (unsigned char) c == 0)
		return ((char *) s);
	return (NULL);
}
