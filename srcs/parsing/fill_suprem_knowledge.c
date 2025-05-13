/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_suprem_knowledge.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:40:08 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/08 13:12:45 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	fill_s_k_ws_lst(t_data **s_k)
// {

// }

int	count_letters(char *str)
{
	int	i;
	int	word;
	int	quote;
	char	c;

	i = 0;
	word = 0;
	quote = 0;
	while (str[i] && word == 0)
	{
		while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
			i++;
		if (str[i] && (str[i] != 32 || (str[i] <= 8 || str[i] >= 13)))
		{
			// word++;
			if (word == 1)
				return (i);
			quote = 0;
			while ((str[i] && (str[i] != 32 && (str[i] <= 8 || str[i] >= 13))))
			{
				if (i == 0 && ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
				{
					i += 2;
					return (i);
				}
				if (i != 0 && ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
				{
					word = i; // modif a faire on peut pas laisser word
					i += 2;
					return (word);
				}
				if (i == 0 && (str[i] == '>' || str[i] =='<' || str[i] =='|'))
				{
					i++;
					return (i);
				}
				if (i != 0 && (str[i] == '>' || str[i] =='<' || str[i] =='|'))
				{
					word = i;
					i++;
					return (word);
				}
				if (str[i] == '\'' || str[i] == '"')
				{
					quote = 1;
					c = str[i];

					while (str[i]) // && (str[i] != '\'' || str[i] != '"'))
					{
						i++;
						if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
						{
							quote = 0;

							while (str[i])
							{
								if (str[i] == 32 && (quote % 2) == 0)
								{
									quote = 0;
									break;
								}
								i++;
								if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
								{
									quote++;
								}
							}
						}
						if (quote == 0)
						{
							word++;
							if (word == 1)
								return (i);
							break ;
						}
					}
				}
				if(str[i] != '\0')
					i++;
			}
			word++;
		}
	}
	// printf ("i : %d\n", i);
	return (i);
}

int	pipe_quota(char *str, t_data **s_k)
{
	int	i = 0;
	int	pipe = 0;

	if(!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '|')
			pipe++;
		i++;
	}
	(*s_k)->pipe_quo = pipe;
	// printf ("pipe_quo : %d\n\n", (*s_k)->pipe_quo);
	return (0);
}

int	quote_verif(char *str, t_data **s_k)
{
	int	i;
	int	quote;
	int	d_quote;
	
	i = 0;
	quote = 0;
	d_quote = 0;
	if(!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '"')
			d_quote++;
		if (str[i] == '\'')
			quote++;
		i++;
	}
	(*s_k)->stat_quo = d_quote + quote;
	// printf ("stat_quo : %d\n\n", (*s_k)->stat_quo);
	if (quote % 2 != 0)
		return (printf("missing quote\n"));
	if (d_quote % 2 != 0)
		return (printf("missing double quote\n"));
	return (0);
}


void	fill_s_k_tab(t_data **s_k, char *str)
{
	int	i;
	// int	k;
	int	count_l;
	int	count_w;

	i = 0;
	(*s_k)->tab_len = 0;
	count_w = 0;
	count_w = count_words(str);
	// printf ("count_w : %d\n", count_w);
	(*s_k)->rl_tab = malloc(sizeof(char *) * (count_w + 1));
	while (str[0] == 32 || (str[0] >= 8  && str[0] <= 13 ))
	{
		str++;
	}
	while (str[0])
	{
		while (*str && ((*str >= 8 && *str <= 13) || *str == 32))
			str++;
		// k = 0;
		count_l = 0;
		count_l = count_letters(str);
		// printf ("count_l : %d\n", count_l);
		(*s_k)->rl_tab[i] = malloc(sizeof(char) * (count_l + 1));
		copy_word((*s_k)->rl_tab[i], &str, count_l);
		// if (count_l)
		i++;
		while (*str && ((*str >= 8 && *str <= 13) || *str == 32))
			str++;
	}
	
	// printf ("HALLO ??? i : %d\n", i);
	(*s_k)->rl_tab[i] = NULL;
	(*s_k)->tab_len = i;
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
	
	// fill_s_k_tab(s_k, str);
	fill_tabs(s_k, str);
}

void	free_glt(t_data **s_k)
{
	int	i;
	int	len;
	
	i = 0;
	len = (*s_k)->tab_len;
	if ((*s_k)->glutto_tab)
	{
		while (i <= len)
		{
			free((*s_k)->glutto_tab[i]);
			(*s_k)->glutto_tab[i] = NULL;
			i++;
		}
		// (*s_k)->tab_len = 0;
		len = 0;
	}
	if ((*s_k)->glutto_tab)
	{
		free((*s_k)->glutto_tab);
		(*s_k)->glutto_tab = NULL;
	}
		// if ((*s_k)->tab_env)
	// 	free_tab((*s_k)->tab_env);
}

void	free_s_k(t_data **s_k)
{
	int	i;
	int	len;
	
	i = 0;
	len = (*s_k)->tab_len;
	if ((*s_k)->rl_tab)
	{
		while (i <= len)
		{
			free((*s_k)->rl_tab[i]);
			(*s_k)->rl_tab[i] = NULL;
			i++;
		}
		len = 0;
	}
	if ((*s_k)->rl_tab)
	{
		free((*s_k)->rl_tab);
		(*s_k)->rl_tab = NULL;
	}
	if ((*s_k)->tab_env)
	{
		free_tab((*s_k)->tab_env);
		(*s_k)->tab_env = NULL;
	}
}


void	free_data(t_data **s_k)
{
	free_s_k(s_k);
	free_glt(s_k);
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
	(*s_k)->glutto_tab = NULL;
	(*s_k)->re_token = NULL;
	(*s_k)->tab_env = NULL;
	(*s_k)->pipe_nbr = 0;
	*(*s_k)->pipefd1 = 0;
	*(*s_k)->pipefd2 = 0;
	(*s_k)->stat_quo = 0;
	(*s_k)->pipe_quo = 0;
	fill_tab_env(s_k, envp);

	(*s_k)->tab_len = 0;
}
