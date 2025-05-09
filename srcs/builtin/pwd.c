/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:21:46 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/08 14:26:11 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*position;

	position = getcwd(NULL, 0);
	if (!position)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", position);
	free (position);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	if (argc > 1)
// 		printf("%s", argv[1]);
// 	ft_pwd();
// 	return(0);
// }
