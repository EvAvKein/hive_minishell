/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:05:11 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/15 09:35:12 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_elements(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while(envp[i])
			i++;
	}
	return (i);
}

char	**dup_envp(char **envp)
{
	int		i;
	int		env_count;
	char	**dup;

	i = 0;
	env_count = get_env_elements(envp);
	dup = ft_calloc(env_count + 1, sizeof(char *));
	while(envp[i])
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
			//TODO: error/cleanup
		i++;
	}
	dup[i] = NULL;
	return(dup);
}

void	free_env_array(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
