/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:24 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/09 07:59:21 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if ((c >= 8 && c <= 13) || c == 32)
	{
		return (0);
	}
	return (1);
}





// void	tokenize(t_data **s_k, t_lst_arg **token)
// {
// 	int		i;
// 	char	*start;

// 	i = 0;
// 	start = NULL;
	
// 	while ((*s_k)->rl_tab[i])
// 	{
// 		printf("rl_tab[%d]: %s\n\n",i, (*s_k)->rl_tab[i]);

// 		rl_lst_addback(token, rl_lst_new(start, (*s_k)->rl_tab[i], i));
// 		printf ("HALLO????");
// 		start = NULL;

// 		i++;
// 	}


// 	t_lst_arg	*nav;
// 	nav = (*token);
// 	i = 0;
// 	while (nav)
// 	{
// 		printf("\ntoken[%d]: %s\n\n\n\n", i, nav->rl_arg);
// 		nav = nav->next;
// 		i++;
// 	}
// }










// void	tokenize(t_data **s_k, t_lst_arg **token)
// {
// 	int		i;

// 	i = 0;
	
// 	while ((*s_k)->rl_tab[i])
// 	{
// 		printf("rl_tab[%d]: %s\n\n",i, (*s_k)->rl_tab[i]);

// 		rl_lst_addback(token, rl_lst_new(&(*s_k)->rl_tab[i][0], (*s_k)->rl_tab[i], i));
// 		printf ("HALLO????");
// 		i++;
// 	}











	
	// while (*str)
	// {
	// 	if (quote)
	// 	{
	// 		if (*str == quote || *str == quote)
	// 		{
	// 			rl_lst_addback(token, rl_lst_new(start, str, i));
	// 			quote = 0;
	// 			start = NULL;
	// 			(*token)->type = QUOTES;
	// 			i++;
	// 		}
	// 	}
	// 	else if (*str == '\'' || *str == '"')
	// 	{
	// 		if (start)
	// 			rl_lst_addback(token, rl_lst_new(start, str, i));
	// 		quote = *str;
	// 		start = str + 1;
	// 	}
	// 	else if (is_whitespace(*str) == 0)
	// 	{
	// 		if (start)
	// 		{
	// 			rl_lst_addback(token, rl_lst_new(start, str + 1, i));
	// 			i++;
	// 			start = NULL;
	// 		}
	// 	}
	// 	else if (ft_strchr("><|", *str))
	// 	{
	// 		if (start)
	// 		{
	// 			rl_lst_addback(token, rl_lst_new(start, str - 1, i));
	// 			i++;
	// 			start = NULL;
	// 		}
	// 		if ((*(str + 1) == '>' && *str == '>') || (*(str + 1) == '<' && *str == '<'))
	// 		{
	// 			rl_lst_addback(token, rl_lst_new(str, str + 1, i));
	// 			i++;
	// 			str++;
	// 			start = NULL;
	// 			(*token)->type = APPEND;
	// 		}
	// 		else
	// 		{
	// 			rl_lst_addback(token, rl_lst_new(str, str, i));
	// 			i++;
	// 			(*token)->type = OPERATORS;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (!start)
	// 			start = str;
	// 	}
	// 	str++;
	// }
	// if (start)
	// {
	// 	rl_lst_addback(token, rl_lst_new(start, str, i));
	// 	i++;
	// }
// 	t_lst_arg	*nav;
// 	nav = (*token);
// 	i = 0;
// 	while (nav)
// 	{
// 		printf("\ntoken[%d]: %s\n\n\n\n", i, nav->rl_arg);
// 		nav = nav->next;
// 		i++;
// 	}
// }











void	tokenize(char *str, t_lst_arg **token)
{
	char	quote;
	char	*start;
	int		i;

	quote = 0;		//" echo "bonjour" > text.txt | cat -e < text.txt
	i = 0;
	start = NULL;
	while (*str)
	{
		if (quote)
		{
			if (*str == quote || *str == quote)
			{
				rl_lst_addback(token, rl_lst_new(start, str, i));
				quote = 0;
				start = NULL;
				(*token)->type = QUOTES;
				i++;
			}
		}
		else if (*str == '\'' || *str == '"')
		{
			if (start)
				rl_lst_addback(token, rl_lst_new(start, str, i));
			quote = *str;
			start = str + 1;
		}
		else if (is_whitespace(*str) == 0)
		{
			if (start)
			{
				rl_lst_addback(token, rl_lst_new(start, str + 1, i));
				i++;
				start = NULL;
			}
		}
		else if (ft_strchr("><|", *str))
		{
			if (start)
			{
				rl_lst_addback(token, rl_lst_new(start, str - 1, i));
				i++;
				start = NULL;
			}
			if ((*(str + 1) == '>' && *str == '>') || (*(str + 1) == '<' && *str == '<'))
			{
				rl_lst_addback(token, rl_lst_new(str, str + 1, i));
				i++;
				str++;
				start = NULL;
				(*token)->type = APPEND;
			}
			else
			{
				rl_lst_addback(token, rl_lst_new(str, str, i));
				i++;
				(*token)->type = OPERATORS;
			}
		}
		else
		{
			if (!start)
				start = str;
		}
		str++;
	}
	if (start)
	{
		rl_lst_addback(token, rl_lst_new(start, str, i));
		i++;
	}
	t_lst_arg	*nav;
	nav = (*token);
	i = 0;
	while (nav)
	{
		// printf("token[%d]: %s\n", i, nav->rl_arg);
		nav = nav->next;
		i++;
	}
}
