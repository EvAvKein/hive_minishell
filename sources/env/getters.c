#include "minishell.h"

/**
 * 
 * @param var_name The name (key) of the environment variable to look for.
 * 
 * @param length   The length of the variable name provided in `var_name`.
 *                 (not measured internally
 *                 due to the function's varied usage).
 * 
 * @returns The memory address where the matching variable is stored,
 *          or `NULL` or no matching environment variable was found.
 * 
 */
char  **env_var_ptr(char *var_name, size_t length)
{
	char    **env;
	size_t	i;

	env = get_shell()->env;
  if (!env)
    return (NULL);
	i = 0;
	while (env[i])
	{
		if (envncmp(env[i], var_name, length))
			return (&env[i]);
		i++;
	}
	return (NULL);
}

/**
 * 
 * @param var_name The name (key) of the environment variable to look for.
 * 
 * @param length   The length of the variable name provided in `var_name`.
 *                 (not measured internally
 *                 due to the function's varied usage).
 * 
 * @returns The full string (key and value) of the matching variable,
 *          or `NULL` or no matching environment variable was found.
 * 
 */
char  *env_var(char *var_name, size_t length)
{
  char  **var_address;

  var_address = env_var_ptr(var_name, length);
  if (!var_address)
    return (NULL);
  return (*var_address);
}

/**
 * 
 * Gets the environment's value for the provided variable name.
 * 
 * @param var_start The start of an enviroment variable name
 *                  to search for inside the env.
 * 
 * @param length   The length of the variable name provided in `var_name`.
 *                 (not measured internally
 *                 due to the function's varied usage).
 * 
 * @returns The memory address (not a duplicate) of the provided
 *          variable's value, no `NULL` if there's no such environment variable.
 * 
 */
char	*env_value(char *var_start, size_t length)
{
	char    *var;
  size_t  i;

	var = env_var(var_start, length);
  if (!var)
		return (NULL);
  i = 0;
  while (is_envname_char(var[i]))
    i++;
  if (var[i] == '=')
    i++;
  return (&var[i]);
}
