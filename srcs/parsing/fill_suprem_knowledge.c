/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_suprem_knowledge.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:40:08 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/22 13:07:38 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	fill_s_k_ws_lst(t_data **s_k)
// {

// }

int	count_letters(int k, int count, char *str)
{
	while (str[k] && (str[k] > 13 || str[k] < 8) && str[k] != 32)
	{
		if (str[k] != '"' && str[k] != '\'')
			count++;
		k++;
	}
	return (count);
}

void	fill_s_k_tab(t_data **s_k, char *str)
{
	int	quote;
	int	i;
	char *start;

	i = 0;
	quote = 0;
	start = NULL;
	while ((*str >= 8 && *str <= 13) || *str == 32)
		str++;
	(*s_k)->rl_tab = ft_calloc(sizeof(char *), 70000);
	printf("%s\n", str);
	while (*str != '\0')
	{
		if (quote == 0 && (*str == '\'' || *str == '"'))
		{
			if (*str == '\'')
			{
				start = str + 1;
				quote = 1;
			}
			else
			{
				start = str + 1;
				quote = 2;
			}
		}
		else if ((quote == 1 || quote == 2) && (*str == '\'' || *str == '"'))
		{
			if (quote == 1 && *str == '\'')
			{
				quote = 0;
				// (*s_k)->rl_tab[i] = malloc(sizeof(char) * ((str - start) + 1));
				ft_strncpy((*s_k)->rl_tab[i], start, (&str - &start)); //!!!!!!!!!!fonction a remplacer par une de nos mains!!!!!!!!!!!!!!!!*/
				start = NULL;
			}
			else if (quote == 2 && *str == '"')
			{
				quote = 0;
				// (*s_k)->rl_tab[i] = malloc(sizeof(char) * ((str - start) + 1));
				ft_strncpy((*s_k)->rl_tab[i], start, (&str - &start)); //!!!!!!!!!!fonction a remplacer par une de nos mains!!!!!!!!!!!!!!!!*/
				start =NULL;
			}
		}
		else if (start == NULL && *str > 32)
		{
			start = str;
		}
		else if (start && (*(str + 1) == 32 || (*(str + 1) >= 8 && *(str + 1) <= 13) || *(str + 1) == '\0'))
		{
			// (*s_k)->rl_tab[i] = malloc(sizeof(char) * ((str - start) + 1));
			// printf("%ld\n", (str - start));
			ft_strncpy((*s_k)->rl_tab[i], start, ((str - start) + 1));
		}
		str++;
	}
}





// void	fill_s_k_tab(t_data **s_k, char *str)
// {
// 	// int	i;
// 	// int	k;
// 	// int	count;

// 	// i = 0;
// 	// (*s_k)->tab_len = 0;
// 	// (*s_k)->rl_tab = malloc(sizeof(char *) * (count_words(str) + 1));
// 	// while (str[0] == '"' || str[0] == '\'' || str[0] == 32 || (str[0] >= 8  && str[0] <= 13 ))
// 	// {
// 	// 	printf("%c\n", str[0]);
// 	// 	str++;
// 	// }
// 	// while (str[0] /*&& str[0] != '"' && str[0] != '\''*/)
// 	// {
// 	// 	count = 0;
// 	// 	k = 0;
// 	// 	count = count_letters(k, count, str);
// 	// 	(*s_k)->rl_tab[i] = malloc(sizeof(char) * (count + 1));
// 	// 	copy_word((*s_k)->rl_tab[i], &str);
// 	// 	if (count)
// 	// 		i++;
// 	// 	while (*str && ((*str >= 8 && *str <= 13) || *str == 32))
// 	// 		str++;
// 	// }
// 	// (*s_k)->rl_tab[i] = NULL;
// 	// (*s_k)->tab_len = i;
// }

void	fill_suprem_knowledge(t_data **s_k, char *str)
{
	if (!s_k || !(*s_k))
		return ;
	fill_s_k_tab(s_k, str);
}

void	free_data(t_data **s_k)
{
	int	i;
	t_data	*data = *s_k;

	i = 0;
	if ((*s_k)->rl_tab)
	{
		while (i <= (*s_k)->tab_len)
		{
			free((*s_k)->rl_tab[i]);
			i++;
		}
		(*s_k)->tab_len = 0;
	}
	if (data->rl_tab)
		free(data->rl_tab);
	if (data->tab_env)
		free_tab(data->tab_env);
}

void	init_suprem_knowledge(t_data **s_k, char **envp)
{
	(*s_k) = malloc(sizeof(t_data));
	if (!s_k)
	{
		printf("mince alors\n");
		return ;
	}
	(*s_k)->rl_tab = NULL;
	(*s_k)->tab_env = NULL;
	(*s_k)->pipe_nbr = 0;
	init_pipefd((*s_k)->pipefd);
	fill_tab_env(s_k, envp);

	(*s_k)->tab_len = 0;
}
