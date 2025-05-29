/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:09:42 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/30 11:27:58 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	replace_env(char **new_env)
{
	free(get_shell()->env);
	get_shell()->env = new_env;
	return (true);
}

/**
 * 
 * Adds the provided environment variable to the shell's environment,
 * replacing an existing variable with the same name is such exists.
 * 
 * @param new_var A variable to be added/updated to the shell's environment.
 * 
 * Rejecting env variables with invalid names is
 * the responsibility of the calling function.
 * 
 */
bool	env_add(char *new_var)
{
	char	**var_exists;
	char	**larger_env;
	size_t	i;

	var_exists = env_var_ptr(new_var);
	if (var_exists)
	{
		free(*var_exists);
		*var_exists = new_var;
		return (true);
	}
	larger_env = ft_calloc(str_arr_count(get_shell()->env) + 2, sizeof(char *));
	if (!larger_env)
	{
		print_err("env: ", strerror(ENOMEM));
		return (false);
	}
	i = 0;
	while (get_shell()->env[i])
	{
		larger_env[i] = get_shell()->env[i];
		i++;
	}
	larger_env[i] = new_var;
	return (replace_env(larger_env));
}

/**
 * 
 * Remove the variable with the provided name from the shell's environment.
 * 
 * @returns Whether the provided `var_to_remove` matched an existing
 *          environment variable.
 * 
 */
bool	env_remove(char *var_to_remove)
{
	const char		**var_found = (const char **) env_var_ptr(var_to_remove);
	char			**smaller_env;
	size_t			copy_i;
	size_t			paste_i;

	if (!var_found)
		return (false);
	copy_i = 0;
	paste_i = 0;
	smaller_env = ft_calloc(str_arr_count(get_shell()->env), sizeof(char *));
	if (smaller_env)
	{
		while (get_shell()->env[copy_i])
		{
			if (&get_shell()->env[copy_i] == (char **) var_found)
				free(get_shell()->env[copy_i++]);
			else
				smaller_env[paste_i++] = get_shell()->env[copy_i++];
		}
		return (replace_env(smaller_env));
	}
	((char **)(ft_memmove(var_found, var_found + sizeof(char *),
			str_arr_count((char **) var_found + sizeof(char *)))))
		[str_arr_count(get_shell()->env) - 1] = NULL;
	return (true);
}
