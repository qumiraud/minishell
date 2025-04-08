/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solotnbrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:30:21 by qumiraud          #+#    #+#             */
/*   Updated: 2024/11/05 11:48:23 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int nbr)
{
	int	i;

	i = 0;
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		i = 11;
	}
	else if (nbr < 0)
	{
		i += write(1, "-", 1);
		nbr = -nbr;
		i += ft_printnbr(nbr);
	}
	else if (nbr > 9)
	{
		i += ft_printnbr(nbr / 10);
		i += ft_putcharpf_fd(nbr % 10 + '0', 1);
		return (i);
	}
	else
	{
		i += ft_putcharpf_fd(nbr + '0', 1);
	}
	return (i);
}

int	ft_printunsnbr(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr > 9)
	{
		i += ft_printunsnbr(nbr / 10);
		i += ft_putcharpf_fd(nbr % 10 + '0', 1);
	}
	else
		i += ft_putcharpf_fd(nbr % 10 + '0', 1);
	return (i);
}

int	ft_printhexanbr(unsigned int nbr)
{
	int		j;
	char	*hexa;

	hexa = "0123456789abcdef";
	j = 0;
	if (nbr < 16)
		j += ft_putcharpf_fd(hexa[nbr], 1);
	else
	{
		j += ft_printhexanbr(nbr / 16);
		j += ft_printhexanbr(nbr % 16);
	}
	return (j);
}

int	ft_printuphexanbr(unsigned int nbr)
{
	int		i;
	char	*hexa;

	hexa = "0123456789ABCDEF";
	i = 0;
	if (nbr < 16)
		i += ft_putcharpf_fd(hexa[nbr], 1);
	else
	{
		i += ft_printuphexanbr(nbr / 16);
		i += ft_printuphexanbr(nbr % 16);
	}
	return (i);
}

int	ft_printphexanbr(unsigned long int nbr)
{
	int		j;
	char	*hexa;

	hexa = "0123456789abcdef";
	j = 0;
	if (nbr < 16)
		j += ft_putcharpf_fd(hexa[nbr], 1);
	else
	{
		j += ft_printphexanbr(nbr / 16);
		j += ft_printphexanbr(nbr % 16);
	}
	return (j);
}
