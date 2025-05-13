// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   re_token.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/07 13:03:33 by pjurdana          #+#    #+#             */
// /*   Updated: 2025/05/07 13:32:35 by pjurdana         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"


// // void	re_token_lt(t_data **s_k)
// // {
	
// // }



// int	re_token_wd(t_data **s_k)
// {
// 	char	**str;
// 	int		i = 0;
// 	int		j = 0;
// 	int		word = 0;



// 	str = (*s_k)->glutto_tab;

// 	while (str[i])
// 	{
// 		word++;
// 		j = 0;
// 		while (str[i][j])
// 		{
// 			if ((str[i][j] == '>' && str[i][j +1] == '>') || (str[i][j] == '<' && str[i][j + 1] == '<'))
// 			{
// 				word++;
// 				printf ("\n\n\nHALLO???\n\n\n");
// 				j += 2;
// 				continue;
// 			}
// 			else if (str[i][j] == '>' || str[i][j] == '<' || str[i][j] == '|')
// 			{
// 				printf ("\n\n\nALED???\n\n\n");

// 				word++;
// 				j++;
// 				continue;
// 			}
// 			j++;


// 		}
// 		i++;

// 	}

// 	printf ("word : %d\n", word);

// 	return (word);

// }