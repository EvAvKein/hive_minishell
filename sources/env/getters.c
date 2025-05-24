/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:02:44 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/24 14:43:24 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @param var_name The name (key) of the environment variable to look for.
 * 
 * @returns The memory address where the matching variable is stored,
 *          or `NULL` or no matching environment variable was found.
 * 
 */
char  **env_var_ptr(char *var_name)
{
	char    **env;
	size_t	i;
  size_t  name_len;

	env = get_shell()->env;
  if (!env)
    return (NULL);
	i = 0;
  name_len = env_name_len(var_name);
	while (env[i])
	{
		if (envncmp(env[i], var_name, name_len))
			return (&env[i]);
		i++;
	}
	return (NULL);
}

/**
 * 
 * @param var_name The name (key) of the environment variable to look for.
 * 
 * @returns The full string (key and value) of the matching variable,
 *          or `NULL` or no matching environment variable was found.
 * 
 */
char  *env_var(char *var_name)
{
  char  **var_address;

  var_address = env_var_ptr(var_name);
  if (!var_address)
    return (NULL);
  return (*var_address);
}

/**
 * 
 * Gets the environment's value for the provided variable name.
 * 
 * @param var_name The name (key) of the environment variable to look for.
 * 
 * @returns The memory address (not a duplicate) of the provided
 *          variable's value, no `NULL` if there's no such environment variable.
 * 
 */
char	*env_value(char *var_name)
{
	char    *var;
  size_t  i;

	var = env_var(var_name);
  if (!var)
		return (NULL);
  i = 0;
  while (is_envname_char(var[i]))
    i++;
  if (var[i] == '=')
    i++;
  return (&var[i]);
}
