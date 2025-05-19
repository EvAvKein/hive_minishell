/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:03:34 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/19 15:39:11 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *
 * Checks whether the provided character is a valid character
 * for an environment variable name.
 * 
 * @param c The provided character.
 *  
 * @returns Whether the provided character a valid variable name character.
 * 
 */
static inline bool	is_envname_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * 
 * Counts and returns the length
 * of a valid environment variable from `var_start`.
 *
 * @param var_start  The beginning of the string from which to count.
 * 
 * @returns The length of the valid environment variable name
 *          which starts at `var_start`.
 * 
 */
size_t	env_name_len(char *var_start)
{
	size_t	i;

	i = 0;
	while (is_envname_char(var_start[i]))
		i++;
	return (i);
}

/**
 * 
 * Compares whether an env string is the same as the given variable name.
 * 
 * @param env_str   An entire string from the shell's enviroment.
 * 
 * @param var_start The start of the variable name
 *                  with which to check for a match.
 * 
 * @param cmp       The maximum amount of characters to compare.
 * 
 * @returns Whether `var_name` is the same as the name in the given `env_str`.
 * 
 */
bool	envncmp(char *env_str, char *var_start, size_t cmp)
{
	size_t	i;

	i = 0;
	if (!env_str || !var_start || !cmp)
		return (false);
	while (i < cmp && env_str[i] && env_str[i] != '=' && var_start[i])
	{
		if (env_str[i] != var_start[i])
			return (false);
		i++;
	}
	if (!i || (env_str[i] && env_str[i] != '=')
		|| is_envname_char(var_start[i]))
		return (false);
	return (true);
}

/**
 * 
 * Gets the environment's value for the provided variable name.
 * 
 * @param var_start The start of an enviroment variable name
 *                  to search for inside the env.
 * 
 * @returns The memory address (not a duplicate) of the provided
 *          variable's value, no `NULL` if there's no such environment variable.
 * 
 */
char	*env_value(char *var_start)
{
	char	**env;
	size_t	i;
	char	*var_found;

	env = get_shell();
	i = 0;
	if (!var_start)
		return (NULL);
	while (env[i])
	{
		if (envncmp(env[i], var_start, env_name_len(var_start)))
		{
			var_found = env[i];
			i = 0;
			while (is_envname_char(var_found[i]))
				i++;
			if (var_found[i] == '=')
				i++;
			return (&var_found[i]);
		}
		i++;
	}
	return (NULL);
}
