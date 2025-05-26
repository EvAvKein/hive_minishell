/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:23:19 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/26 10:30:48 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @return The shell's default env (or `NULL` if memory allocation failed).
 * 
 */
static char	**default_env()
{
	char	**ret;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup("SHLVL=1");
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	return (ret);
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
