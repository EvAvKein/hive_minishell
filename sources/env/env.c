/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:23:19 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/27 20:31:03 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @return The shell's default env (or `NULL` on memory allocation failure).
 * 
 */
static char	**default_env()
{
	char	**env;

	env = ft_calloc(2, sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = ft_strdup("SHLVL=1");
	if (!env[0])
	{
		free(env);
		return (NULL);
	}
	return (env);
}

/**
 * 
 * Creates a duplicate of the provided `shlvl` in which the value is one bigger.
 * If the SHLVL's value is empty or anything other than digits,
 * the value of the returned SHLVL is 1.
 * 
 * @param shlvl A string beginning with "SHLVL=",
 *              preferably (but not necessrily) followed by an unsigned number.
 * 
 * @returns A heap-allocated string starting with "SHLVL=" followed by a number
 *          (or `NULL` on memory allocation failure).
 * 
 */
char	*dup_shlvl_incremented(char *shlvl)
{
	size_t	i;
	char	*bigger_shlvl;

	i = ft_strchr(shlvl, '=') - shlvl + 1;
	while (shlvl[i])
	{
		if (!ft_isdigit(shlvl[i++]))
			return (ft_strdup("SHLVL=1"));
	}
	if (shlvl[--i] == '=')
		return (ft_strdup("SHLVL=1"));
	if (shlvl[i] < '9')
	{
		bigger_shlvl = ft_strdup(shlvl);
		if (!bigger_shlvl)
			return (NULL);
		bigger_shlvl[i]++;
		return (bigger_shlvl);
	}
	bigger_shlvl = ft_strjoin(shlvl, " ");
	if (!bigger_shlvl)
		return (NULL);
	bigger_shlvl[i + 1] = '\0';
	increment_postfixed_num(bigger_shlvl);
	return (bigger_shlvl);
}


/**
 * 
 * @param env An array of strings to be duplicated.
 * 
 * @returns A duplicate of the provided env,
 *          containing copies of the inside strings.
 * 
 */
char	**env_dup(char **env)
{
	size_t	i;
	char	**dup;

	i = 0;
	if (!env || !env[0])
		return (default_env());
	dup = ft_calloc(str_arr_count(env) + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			dup[i] = dup_shlvl_incremented(env[i]);
		else
			dup[i] = ft_strdup(env[i]);
		if (!dup[i])
		{
			free_str_arr(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}

/**
 * 
 * Initializes the shell's env based on the `
 * envp` inherited from the parent shell.
 * 
 */
void	init_env(char **envp)
{
	get_shell()->env = env_dup(envp);
	if (!get_shell()->env)
	{
		print_err("env creation failed: ", strerror(ENOMEM));
		shell_exit(EXIT_FAILURE);
	}
}
