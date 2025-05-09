/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:13:27 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/09 11:48:26 by qumiraud         ###   ########.fr       */
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

int	ft_export(char **args, char ***envp)
{
	int		i;
	int		var_len;
	char	**new_envp;
	int		env_len;
	int		arg_nbr;
	int	found;

	arg_nbr = 1;
	i = 0;
	if (!args[1])
	{
		while ((*envp)[i])
		{
			printf("%s\n", (*envp)[i]);
			i++;
		}
		return (0);
	}
	while (args[arg_nbr])
	{
		i = 0;
		found = 0;
		if (!ft_strchr(args[arg_nbr], '='))
		{
			arg_nbr++;
			continue;
		}
		var_len = ft_varlen(args[arg_nbr], '=');
		while ((*envp)[i])
		{
			if (ft_strncmp((*envp)[i], args[arg_nbr], var_len) == 0 && (*envp)[i][var_len] == '=')
			{
				free((*envp)[i]);
				(*envp)[i] = ft_strdup(args[arg_nbr]);
				found = 1;
				break;
			}
			i++;
		}
		if (!found)
		{
			i = 0;
			env_len = 0;
			while ((*envp)[env_len])
				env_len++;
			new_envp = malloc(sizeof(char *) * (env_len + 2));
			if (!new_envp)
				return (1);
			while (i < env_len)
			{
				new_envp[i] = (*envp)[i];
				i++;
			}
			new_envp[env_len] = ft_strdup(args[arg_nbr]);
			new_envp[env_len + 1] = NULL;
			free(*envp);
			(*envp) = new_envp;
		}
		arg_nbr++;
	}
	return (0);
}
//!Test creer par claude.ai!//
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Déclarations des fonctions nécessaires au test
// int ft_export(char **args, char ***envp);
// int ft_varlen(char *str, char c);

// // Fonction pour dupliquer une chaîne de caractères (équivalent à strdup)
// char *ft_strdup(const char *s) {
//     char *dup;
//     size_t len = strlen(s) + 1;

//     dup = malloc(len);
//     if (dup == NULL)
//         return NULL;

//     return memcpy(dup, s, len);
// }

// // Fonction pour comparer n caractères de deux chaînes
// int ft_strncmp(const char *s1, const char *s2, size_t n) {
//     size_t i = 0;

//     if (n == 0)
//         return 0;

//     while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i])
//         i++;

//     return (unsigned char)s1[i] - (unsigned char)s2[i];
// }

// // Fonction pour chercher un caractère dans une chaîne
// char *ft_strchr(const char *s, int c) {
//     while (*s) {
//         if (*s == (char)c)
//             return (char *)s;
//         s++;
//     }
//     if ((char)c == '\0')
//         return (char *)s;
//     return NULL;
// }

// // Fonction pour afficher l'environnement
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
//     char **env = malloc(sizeof(char *) * 4);
//     env[0] = ft_strdup("PATH=/usr/bin:/bin");
//     env[1] = ft_strdup("HOME=/home/user");
//     env[2] = ft_strdup("USER=testuser");
//     env[3] = NULL;
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

//     printf("Test de la fonction ft_export\n");

//     // Affichage de l'environnement initial
//     print_envv(env);

//     // Test 1: export sans arguments (affiche l'environnement)
//     printf("Test 1: export sans arguments\n");
//     args = malloc(sizeof(char *) * 2);
//     args[0] = ft_strdup("export");
//     args[1] = NULL;
//     ft_export(args, &env);
//     free(args[0]);
//     free(args);

//     // Test 2: ajouter une nouvelle variable
//     printf("Test 2: ajouter une nouvelle variable (NEWVAR=value)\n");
//     args = malloc(sizeof(char *) * 3);
//     args[0] = ft_strdup("export");
//     args[1] = ft_strdup("NEWVAR=value");
//     args[2] = NULL;
//     ft_export(args, &env);
//     print_envv(env);
//     free(args[0]);
//     free(args[1]);
//     free(args);

//     // Test 3: modifier une variable existante
//     printf("Test 3: modifier une variable existante (USER=newuser)\n");
//     args = malloc(sizeof(char *) * 3);
//     args[0] = ft_strdup("export");
//     args[1] = ft_strdup("USER=newuser");
//     args[2] = NULL;
//     ft_export(args, &env);
//     print_envv(env);
//     free(args[0]);
//     free(args[1]);
//     free(args);

//     // Test 4: ajouter plusieurs variables
//     printf("Test 4: ajouter plusieurs variables (VAR1=val1 et VAR2=val2)\n");
//     args = malloc(sizeof(char *) * 4);
//     args[0] = ft_strdup("export");
//     args[1] = ft_strdup("VAR1=val1");
//     args[2] = ft_strdup("VAR2=val2");
//     args[3] = NULL;
//     ft_export(args, &env);
//     print_envv(env);
//     free(args[0]);
//     free(args[1]);
//     free(args[2]);
//     free(args);

//     // Test 5: argument sans '='
//     printf("Test 5: argument sans '=' (TESTVAR)\n");
//     args = malloc(sizeof(char *) * 3);
//     args[0] = ft_strdup("export");
//     args[1] = ft_strdup("TESTVAR");
//     args[2] = NULL;
//     ft_export(args, &env);
//     print_envv(env);
//     free(args[0]);
//     free(args[1]);
//     free(args);

//     // Libération de la mémoire
//     free_env(env);

//     return 0;
// }
