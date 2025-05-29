/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:02:41 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/29 18:27:55 by ekeinan          ###   ########.fr       */
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
inline bool	is_envname_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * 
 * @param new_env A new potential environment variable
 *                (as in an `export` arg).
 * 
 * @returns Whether the provided environment variable name is valid.
 * 
 */
bool	is_valid_envname(char *new_env)
{
	size_t	i;

	i = 0;
	if (!new_env || ft_isdigit(new_env[i]))
		return (false);
	while (new_env[i] && new_env[i] != '=')
		if (!is_envname_char(new_env[i++]))
			return (false);
	return (i > 0);
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
