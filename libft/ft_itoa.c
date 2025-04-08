/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:14:50 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 16:53:30 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sizen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_sizen(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		i = 1;
		str[0] = '-';
		n = -n;
	}
	while (len > i)
	{
		str[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}
