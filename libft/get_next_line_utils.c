/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:32:33 by qumiraud          #+#    #+#             */
/*   Updated: 2024/11/20 11:08:05 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr_gnl(char *str, char c)
{
	while (*str)
	{
		if (*str == c || *str + 1 == '\0')
			return (1);
		str++;
	}
	return (0);
}

int	ft_strchrlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

void	*ft_clean_malloc(char *str, size_t len)
{
	char	*newspace;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[0] == '\0')
		return (NULL);
	newspace = malloc(len + 1 * sizeof(char));
	if (!newspace)
		return (NULL);
	while (i <= (int) len)
	{
		newspace[i] = '\0';
		i++;
	}
	return (newspace);
}

char	*ft_strdupandfree(char *s)
{
	char	*dups;
	int		i;

	i = 0;
	dups = ft_clean_malloc(s, ft_strlen_gnl(s));
	if (dups == NULL)
	{
		free (s);
		return (NULL);
	}
	while (s[i])
	{
		dups[i] = s[i];
		i++;
	}
	dups[i] = '\0';
	free(s);
	return (dups);
}
