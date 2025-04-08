/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:53:51 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 16:49:32 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char	*nptr)
{
	char	*astr;
	int		n;
	int		sign;

	n = 0;
	sign = 1;
	astr = (char *) nptr;
	while ((*astr >= 9 && *astr <= 13) || *astr == ' ')
		astr++;
	if (*astr == '-' || *astr == '+')
	{
		if (*astr == '-')
			sign = -1;
		astr++;
	}
	while (*astr >= '0' && *astr <= '9')
	{
		n = n * 10 + (*astr - 48);
		astr++;
	}
	return (n * sign);
}
