/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:19:22 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/09 11:48:05 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include "libft/libft.h"


int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
// #include <stdio.h>

// int	main(int argc, char **argv, char **envp)
// {
// 	if (argc != 1)
// 	{
// 		argv[0] = NULL;
// 		return (1);
// 	}
// 	ft_env(envp);
// 	return (0);
// }
