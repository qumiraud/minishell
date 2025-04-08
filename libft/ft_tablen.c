/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:24:43 by quentin           #+#    #+#             */
/*   Updated: 2025/02/24 09:48:47 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		i++;
	}
	return (i);
}

// int	main(int argc, char **argv)
// {
// 	if (argc < 3)
// 		return (1);
// 	else
// 	{
// 		int	tablen;

// 		tablen = ft_tablen(argv);
// 		printf("tablen : %d\n", tablen);
// 		return (0);
// 	}
// }