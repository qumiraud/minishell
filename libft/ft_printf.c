/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:45:27 by qumiraud          #+#    #+#             */
/*   Updated: 2024/11/05 15:38:53 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	count = 0;
	va_start(args, str);
	i = 0;
	if (!str || !*str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_selectpf(args, str[i]);
		}
		else
			count += write (1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
