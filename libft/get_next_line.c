/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:53:47 by qumiraud          #+#    #+#             */
/*   Updated: 2024/11/20 11:09:30 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_whatif_badnb_read(int nb_read, char *bag)
{
	if (nb_read == -1)
	{
		free(bag);
		if (nb_read == -1)
			return (1);
	}
	if (nb_read == 0)
	{
		free(bag);
		return (2);
	}
	return (0);
}

char	*ft_newcontent(char *s1)
{
	char	*ncontent;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && s1[i - 1] != '\n')
		i++;
	ncontent = ft_clean_malloc(s1, ft_strlen_gnl(s1 + i));
	while (s1[i])
	{
		ncontent[j] = s1[i];
		i++;
		j++;
	}
	ncontent[j] = '\0';
	free(s1);
	return (ncontent);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	int		i;

	i = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s3 = ft_strdupandfree(s2);
	else if (!s2)
		s3 = ft_strdupandfree(s1);
	else
	{
		s3 = ft_clean_malloc(s1, ft_strlen_gnl(s1) + ft_strlen_gnl(s2));
		while (s1[++i])
			s3[i] = s1[i];
		i = -1;
		while (s2[++i])
			s3[ft_strlen_gnl(s1) + i] = s2[i];
		free(s1);
		free(s2);
	}
	return (s3);
}

char	*ft_read(int fd, char	*content)
{
	t_buffer	bag;
	char		*tmp;
	int			nb_read;

	tmp = NULL;
	nb_read = -1;
	while (nb_read != 0)
	{
		bag.buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!bag.buffer)
			return (NULL);
		nb_read = read(fd, bag.buffer, BUFFER_SIZE);
		if (nb_read != 0 && ft_whatif_badnb_read(nb_read, bag.buffer) == 1)
			return (NULL);
		if (nb_read != -1 && ft_whatif_badnb_read(nb_read, bag.buffer) == 2)
			break ;
		bag.buffer[nb_read] = '\0';
		if (content)
			tmp = ft_strdupandfree(content);
		content = ft_strjoin_gnl(tmp, bag.buffer);
		if (ft_strchr_gnl(content, '\n') > 0)
			break ;
	}
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*content = NULL;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content = ft_read(fd, content);
	line = ft_clean_malloc(content, ft_strchrlen(content) + 1);
	while (i < ft_strlen_gnl(content))
	{
		line[i] = content[i];
		if (content[i] == '\n')
			break ;
		i++;
	}
	if (content && content[0] != '\0')
		content = ft_newcontent(content);
	else if (content && content[0] == '\0')
	{
		free(content);
		content = NULL;
	}
	return (line);
}
