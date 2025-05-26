/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:09:42 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/26 09:56:38 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_env(char **new_env)
{
	free(get_shell()->env);
	get_shell()->env = new_env;
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
	if (!larger_env && print_err("env: ", strerror(ENOMEM)))
		return (false);
	i = 0;
	while (get_shell()->env[i])
	{
		larger_env[i] = get_shell()->env[i];
		i++;
	}
	larger_env[i] = new_var;
	replace_env(larger_env);
	return (true);
}

/** Created solely for Norminette line-saving */
typedef struct s_copy_paste_i
{
	size_t	copy;
	size_t	paste;
} t_copy_paste_i;

/**
 * 
 * Remove the variable with the provided name from the shell's environment.
 * 
 * @returns Whether removal was successful.
 * 
 */
bool	env_remove(char *var_to_remove)
{
	const char		**var_found = env_var_ptr(var_to_remove);
	char			**smaller_env;
	t_copy_paste_i	i;

	if (!var_found)
		return (false);
	i = (t_copy_paste_i){.copy = 0, .paste = 0};
	smaller_env = ft_calloc(str_arr_count(get_shell()->env), sizeof(char *));
	if (smaller_env)
	{
		while (get_shell()->env[i.copy])
		{
			if (&get_shell()->env[i.copy] == var_found)
				free(get_shell()->env[i.copy++]);
			else
				get_shell()->env[i.copy++] = smaller_env[i.paste++];
		}
		replace_env(smaller_env);
		return (true);
	}
	free(var_found);
	((char **) (ft_memmove(var_found, var_found + sizeof(char *),
		str_arr_count(var_found + sizeof(char *)))))
		[str_arr_count(get_shell()->env) - 1] = NULL;
	return (true);
}
