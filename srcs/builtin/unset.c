/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:39 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/09 11:48:21 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include "libft/libft.h"

static int	ft_varlen(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}

int	ft_suppr_var(char ***envp, int	var_pos)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	i = 0;
	j = 0;
	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (1);
	while (i < count)
	{
		if (i != var_pos)
		{
			new_env[j] = (*envp)[i];
			j++;
		}
		else
			free((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	(*envp) =  new_env;
	return (0);
}

int	ft_unset(char **args, char ***envp)
{
	int		i;
	int		j;
	int		var_len;

	j = 0;
	i = 1;
	if (!args[1])
		return (0);
	while (args[i])
	{
		j = 0;
		while ((*envp)[j])
		{
			var_len = ft_varlen(args[i], '=');
			if (ft_strncmp((*envp)[j], args[i], var_len) == 0 &&
				 args[i][var_len] == '\0' &&
					(*envp)[j][var_len] == '=')
			{
				ft_suppr_var(envp, j);
				break;
			}
			j++;
		}
		i++;
	}
	return (0);
}

// void print_envv(char **env) {
//     int i = 0;
//     printf("\n--- Environnement actuel ---\n");
//     while (env[i]) {
//         printf("%s\n", env[i]);
//         i++;
//     }
//     printf("---------------------------\n\n");
// }

// // Fonction pour initialiser un environnement de test
// char **create_test_env() {
//     char **env = malloc(sizeof(char *) * 7);
//     env[0] = ft_strdup("PATH=/usr/bin:/bin");
//     env[1] = ft_strdup("HOME=/home/user");
//     env[2] = ft_strdup("USER=testuser");
//     env[3] = ft_strdup("LANG=fr_FR.UTF-8");
//     env[4] = ft_strdup("TERM=xterm");
//     env[5] = ft_strdup("SHELL=/bin/bash");
//     env[6] = NULL;
//     return env;
// }

// // Fonction pour libérer l'environnement
// void free_env(char **env) {
//     int i = 0;
//     while (env[i]) {
//         free(env[i]);
//         i++;
//     }
//     free(env);
// }

// int main(void) {
//     char **env = create_test_env();
//     char **args;

//     printf("Test de la fonction ft_unset\n");

//     // Affichage de l'environnement initial
//     printf("Environnement initial :");
//     print_envv(env);

//     // Test 1: unset sans arguments
//     printf("Test 1: unset sans arguments\n");
//     args = malloc(sizeof(char *) * 2);
//     args[0] = ft_strdup("unset");
//     args[1] = NULL;
//     ft_unset(args, &env);
//     printf("Après unset sans arguments :");
//     print_envv(env);
//     free(args[0]);
//     free(args);

//     // Test 2: unset d'une variable existante
//     printf("Test 2: unset d'une variable existante (USER)\n");
//     args = malloc(sizeof(char *) * 3);
//     args[0] = ft_strdup("unset");
//     args[1] = ft_strdup("USER");
//     args[2] = NULL;
//     ft_unset(args, &env);
//     printf("Après unset USER :");
//     print_envv(env);
//     free(args[0]);
//     free(args[1]);
//     free(args);

//     // Test 3: unset d'une variable inexistante
//     printf("Test 3: unset d'une variable inexistante (NOTEXIST)\n");
//     args = malloc(sizeof(char *) * 3);
//     args[0] = ft_strdup("unset");
//     args[1] = ft_strdup("NOTEXIST");
//     args[2] = NULL;
//     ft_unset(args, &env);
//     printf("Après unset NOTEXIST :");
//     print_envv(env);
//     free(args[0]);
//     free(args[1]);
//     free(args);

//     // Test 4: unset de plusieurs variables
//     printf("Test 4: unset de plusieurs variables (HOME LANG SHELL)\n");
//     args = malloc(sizeof(char *) * 5);
//     args[0] = ft_strdup("unset");
//     args[1] = ft_strdup("HOME");
//     args[2] = ft_strdup("LANG");
//     args[3] = ft_strdup("SHELL");
//     args[4] = NULL;
//     ft_unset(args, &env);
//     printf("Après unset HOME LANG SHELL :");
//     print_envv(env);
//     free(args[0]);
//     free(args[1]);
//     free(args[2]);
//     free(args[3]);
//     free(args);

// 	// Test 5: unset d'une variable dont le nom est un préfixe d'une autre
// 	printf("Test 5: Ajout et unset d'une variable dont le nom est un préfixe (PAT vs PATH)\n");

// 	// D'abord ajoutons PAT en conservant correctement les variables existantes
// 	char **new_env = malloc(sizeof(char *) * 4); // 3 éléments + NULL
// 	new_env[0] = ft_strdup("PAT=prefix_test");
// 	new_env[1] = ft_strdup(env[0]); // PATH (duplication au lieu de transfert direct)
// 	new_env[2] = ft_strdup(env[1]); // TERM (duplication au lieu de transfert direct)
// 	new_env[3] = NULL; // Ne pas oublier le terminateur NULL

// 	// Libérer proprement l'ancien environnement
// 	free_env(env);
// 	env = new_env;

// 	printf("Après avoir ajouté PAT :");
// 	print_envv(env);

// 	// Unset PAT
// 	args = malloc(sizeof(char *) * 3);
// 	args[0] = ft_strdup("unset");
// 	args[1] = ft_strdup("PAT");
// 	args[2] = NULL;
// 	ft_unset(args, &env);
// 	printf("Après unset PAT (PATH devrait rester) :");
// 	print_envv(env);
// 	free(args[0]);
// 	free(args[1]);
// 	free(args);

//     // Libération de la mémoire
//     free_env(env);

//     return 0;
// }
