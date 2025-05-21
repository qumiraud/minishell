/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:53:00 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/21 10:36:19 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_words(const char *str)
{

	int	i;
	int	word;
	int	quote;
	int	quotes = 0;
	char	c;

	i = 0;
	word = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
			i++;
		if (str[i] && (str[i] != 32 || (str[i] <= 8 || str[i] >= 13)))
		{
			word++;
			quote = 0;
			while ((str[i] && (str[i] != 32 && (str[i] <= 8 || str[i] >= 13))))
			{
				if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
				{
					if(str[i + 2] == ' ' || (str[i - 1] != ' ' && str[i + 2] != ' '))
						word += 2;
					else
						word++;
					if ((str[i - 1] == ' ' && str[i + 2] == ' '))
						word--;
					i += 2;
				}
				else if ((str[i] == '>' && str[i - 1] != ' ' && str[i + 1] != ' ')
					|| (str[i] == '<' && str[i - 1] != ' ' && str[i + 1] != ' ')
						|| (str[i] == '|' && str[i - 1] != ' ' && str[i + 1] != ' '))// || str[i] == '<' || str[i] == '|')
				{
					word +=2;
				}
				else if ((str[i] == '>' && str[i - 1] == ' ' && str[i + 1] != ' ')
							|| (str[i] == '>' && str[i - 1] != ' ' && str[i + 1] == ' ')
								|| (str[i] == '<' && str[i - 1] == ' ' && str[i + 1] != ' ')
									|| (str[i] == '<' && str[i - 1] != ' ' && str[i + 1] == ' ')
										|| (str[i] == '|' && str[i - 1] == ' ' && str[i + 1] != ' ')
											|| (str[i] == '|' && str[i - 1] != ' ' && str[i + 1] == ' '))
				{
					word++;
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
							while (str[i])
							{
								if (str[i] == 32 && (quotes % 2) == 0)
								{
									quote = 0;
									break;
								}
								i++;
								if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
								{
									quotes++;
								}
							}
						}
						if (quote == 0)
						{
							word++;
							break ;
						}
					}
				}
				if (str[i] != '\0')
					i++;
			}
		}
	}
	// printf("\nword : %d\n\n", word);
	return (word);
}

void	copy_word(char *dest, char **src, int count_l)
{
	int	i = 0;
	
	// printf ("count_l : %d\n", count_l);
	
	while (**src && i != count_l)// && !((**src >= 8 && **src <= 13) || **src == 32))
	{
		if (**src == '"' && **src == '\'')
		count_l++;
		if (**src != '"' && **src != '\'')
		*dest++ = **src;
		(*src)++;
		i++;
	}
	*dest = '\0';
	while (**src && ((**src >= 8 && **src <= 13) || **src == 32))
	src++;
}



void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
