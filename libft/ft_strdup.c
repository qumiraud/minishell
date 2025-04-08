/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:22:47 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 10:00:15 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dups;
	int		i;

	i = 0;
	dups = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (dups == NULL)
		return (NULL);
	while (s[i])
	{
		dups[i] = s[i];
		i++;
	}
	dups[i] = '\0';
	return (dups);
}
