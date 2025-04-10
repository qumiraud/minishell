/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:06:05 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/10 12:27:35 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lst_arg	*rl_lst_new(char *start, char *str, int i)
{
	t_lst_arg	*rl_lst;
	// int	index;
	int length;
	int	j;

	j = 0;
	length = str - start;
	rl_lst = malloc(sizeof(t_lst_arg));
	if (!rl_lst)
	{
		perror("ERROR1\n");
		return (NULL);
	}
	rl_lst->rl_arg = malloc(length * sizeof(char) + 1);
	if (!rl_lst->rl_arg)
	{
		perror("ERROR2\n");
		return (NULL);
	}
	while (start != str)
	{
		rl_lst->rl_arg[j] = *start;
		j++;
		start++;
	}
	rl_lst->rl_arg[j] = '\0';
	rl_lst->index = i;
	rl_lst->next = NULL;
	rl_lst->prev = NULL;
	return (rl_lst);
}

void	rl_lst_addback(t_lst_arg **lst, t_lst_arg *new)
{
	t_lst_arg *nav;
	t_lst_arg *tmp;

	if (!*lst)
	{
		(*lst) = new;
		return;
	}
	nav = (*lst);
	while (nav->next)
		nav = nav->next;
	tmp = nav;
	nav->next = new;
	new->prev = tmp;
}
void	rl_lst_clear(t_lst_arg **lst)
{
	t_lst_arg *nav;

	nav = NULL;
	if (!lst || !(*lst))
		return;
	while (*lst)
	{
		nav = (*lst);
		free(nav->rl_arg);
		*lst = (*lst)->next;
		free(nav);
	}
}
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
void	rl_lst_addfront(t_lst_arg **lst, t_lst_arg *new)
{
	new->next = (*lst);
	(*lst)->prev = new;
	(*lst) = new;
}