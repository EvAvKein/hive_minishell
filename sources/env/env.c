/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:18:23 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/19 11:23:28 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**short_dup()
{
	char	**ret;

	ret = ft_calloc(2, sizeof(char *));
	ret[0] = "SHLVL=1";
	return (ret);
}

char	**dup_envp(char **envp)
{
	int		i;
	int		env_count;
	char	**dup;

	i = 0;
	if (envp[0] == NULL)
		return(short_dup());
	env_count = get_env_elements(envp);
	dup = ft_calloc(env_count + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	while (envp[i])
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
		{
			free_env_array(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
