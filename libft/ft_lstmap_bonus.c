/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:16:29 by qumiraud          #+#    #+#             */
/*   Updated: 2024/10/24 09:01:20 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;

	if (!lst || !(*f) || !(*del))
		return (NULL);
	newlist = ft_lstnew((f)(lst->content));
	if (!newlist)
		ft_lstclear(&newlist, del);
	while (lst->next)
	{
		lst = lst->next;
		if (!newlist)
			ft_lstclear(&newlist, del);
		ft_lstadd_back(&newlist, ft_lstnew((f)(lst->content)));
	}
	return (newlist);
}
