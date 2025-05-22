/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:23:19 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/21 17:46:14 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

char	**dup_env(char **env, size_t extra_size)
{
	size_t	i;
	char	**dup;

	i = 0;
	if (!env || !env[0])
		return(default_env());
	dup = ft_calloc(str_arr_count(env) + extra_size + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	while (env[i])
	{
		dup[i] = ft_strdup(env[i]);
		if (!dup[i])
		{
			free_env_array(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}

void	init_env(char **envp)
{
	get_shell()->env = dup_env(envp, 0);
	if (!get_shell()->env)
	{
		print_err("env creation failed: ", strerror(ENOMEM));
		shell_exit(EXIT_FAILURE);
	}
}
