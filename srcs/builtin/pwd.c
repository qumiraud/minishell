/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:21:46 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 08:24:13 by qumiraud         ###   ########.fr       */
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
