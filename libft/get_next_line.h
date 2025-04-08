/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:32:35 by qumiraud          #+#    #+#             */
/*   Updated: 2024/11/20 11:04:52 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

typedef struct s_buffer
{
	char	*buffer;
}	t_buffer;

char	*get_next_line(int fd);
char	*ft_newcontent(char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_read(int fd, char	*content);
int		ft_strlen_gnl(char *str);
int		ft_strchrlen(char *str);
void	*ft_clean_malloc(char *str, size_t len);
char	*ft_strdupandfree(char *s);
int		ft_strchr_gnl(char *str, char c);
int		ft_whatif_badnb_read(int nb_read, char *bag);

#endif
