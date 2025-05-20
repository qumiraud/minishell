/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathway.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:41:48 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/20 10:53:17 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	*get_way(char **env, char **rl_tab)
{
	int	i;
	int	j;
	char **pathtab;
	char *absolut_path;
	char *tmp;

	i = 0;
	j = 0;
	absolut_path = NULL;
	pathtab = NULL;
	tmp = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pathtab = ft_split(&env[i][5], ':');
			while (pathtab[j])
			{
				// printf("test\n");
				tmp = ft_strjoin(pathtab[j], "/");
				// printf("tmp :%s\n", tmp);
				absolut_path = ft_strjoin(tmp, rl_tab[0]);
				// printf(" %s <---tmp | %s <---find\n", tmp, absolut_path);
				if (access(absolut_path, X_OK) == 0)
				{
					// printf("%s <---find and is X_OK\n", absolut_path);
					free(pathtab);
					return (absolut_path);
				}
				free(tmp);
				free(absolut_path);
				j++;
			}
			free_tab(pathtab);
		}
		i++;
	}
	return (NULL);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	s_k;
// 	char	*cmd_path;

// 	if (argc < 2)
// 	{
// 		printf("Usage: %s <commande>\n", argv[0]);
// 		return (1);
// 	}

// 	// Remplir la structure
// 	s_k.tab_env = envp;

// 	// Simuler rl_tab avec juste une commande
// 	s_k.rl_tab = malloc(sizeof(char *) * 2);
// 	s_k.rl_tab[0] = argv[1];
// 	s_k.rl_tab[1] = NULL;

// 	// Tester la fonction
// 	cmd_path = get_way(&s_k);
// 	if (cmd_path)
// 	{
// 		printf("Chemin trouvé pour \"%s\" : %s\n", argv[1], cmd_path);
// 		free(cmd_path);
// 	}
// 	else
// 		printf("Commande \"%s\" non trouvée dans le PATH.\n", argv[1]);

// 	free(s_k.rl_tab);
// 	return (0);
// }





















// char	*get_way(char **env, char **rl_tab)
// {
// 	int	i;
// 	int	j;
// 	char **pathtab;
// 	char *absolut_path;
// 	char *tmp;

// 	i = 0;
// 	j = 0;
// 	absolut_path = NULL;
// 	pathtab = NULL;
// 	tmp = NULL;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "PATH=", 5) == 0)
// 		{
// 			pathtab = ft_split(&env[i][5], ':');
// 			while (pathtab[j])
// 			{
// 				// printf("pathtab[1] : %s\npathtab[2] : %s\npathtab[3] : %s\netc.\n", pathtab[0], pathtab[1], pathtab[2]);
// 				tmp = ft_strjoin(pathtab[j], "/");
// 				absolut_path = ft_strjoin(tmp, rl_tab[0]);
// 				// printf(" %s <---tmp | %s <---find\n", tmp, absolut_path);
// 				if (access(absolut_path, X_OK) == 0)
// 				{
// 					// printf("%s <---find and is X_OK\n", absolut_path);
// 					return (absolut_path);
// 				}
// 				free(tmp);
// 				free(absolut_path);
// 				j++;
// 			}
// 			free_tab(pathtab);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// // int	main(int argc, char **argv, char **envp)
// // {
// // 	t_data	s_k;
// // 	char	*cmd_path;

// // 	if (argc < 2)
// // 	{
// // 		printf("Usage: %s <commande>\n", argv[0]);
// // 		return (1);
// // 	}

// // 	// Remplir la structure
// // 	s_k.tab_env = envp;

// // 	// Simuler rl_tab avec juste une commande
// // 	s_k.rl_tab = malloc(sizeof(char *) * 2);
// // 	s_k.rl_tab[0] = argv[1];
// // 	s_k.rl_tab[1] = NULL;

// // 	// Tester la fonction
// // 	cmd_path = get_way(&s_k);
// // 	if (cmd_path)
// // 	{
// // 		printf("Chemin trouvé pour \"%s\" : %s\n", argv[1], cmd_path);
// // 		free(cmd_path);
// // 	}
// // 	else
// // 		printf("Commande \"%s\" non trouvée dans le PATH.\n", argv[1]);

// // 	free(s_k.rl_tab);
// // 	return (0);
// // }
