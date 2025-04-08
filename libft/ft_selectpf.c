/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selectpf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:57:54 by qumiraud          #+#    #+#             */
/*   Updated: 2024/11/05 11:49:27 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *s, int fd)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (fd < 0 || s[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		i++;
	}
	j = i;
	write(fd, s, i);
	return (j);
}

int	ft_putcharpf_fd(char c, int fd)
{
	size_t	i;

	i = 0;
	i += write(fd, &c, 1);
	return (i);
}

int	ft_voidpointer(unsigned long int nbr)
{
	int		j;

	j = 0;
	if (!nbr)
	{
		j = write(1, "(nil)", 5);
		return (j);
	}
	j = write(1, "0x", 2);
	j += ft_printphexanbr(nbr);
	return (j);
}

int	ft_selectpf(va_list args, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putcharpf_fd((char)va_arg(args, int), 1);
	else if (c == 's')
		count += ft_printstr(va_arg(args, char *), 1);
	else if (c == 'i' || c == 'd')
		count += ft_printnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_printunsnbr(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_printhexanbr(va_arg(args, unsigned int));
	else if (c == 'X')
		count += ft_printuphexanbr(va_arg(args, unsigned int));
	else if (c == '%')
		count += ft_putcharpf_fd('%', 1);
	else if (c == 'p')
		count += ft_voidpointer(va_arg(args, unsigned long int));
	return (count);
}
