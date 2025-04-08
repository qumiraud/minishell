/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:16:27 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/25 09:34:19 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = NULL;
	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst);
		(del)((*lst)->content);
		*lst = (*lst)->next;
		free(tmp);
	}
	lst = NULL;
}
