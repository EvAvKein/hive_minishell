/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ms_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:57:33 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/17 11:14:04 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_envp(t_shell *shell, char **add, int i, int k)
{
	while(shell->ms_envp[i])
	{
		add[i] = ft_strdup(shell->ms_envp[i]);
		if (!add[i])
		{
			free_env_array(add);
			return (1);
		}
		i++;
	}
	while(shell->nodes->argv[k])
	{
		add[i] = ft_strdup(shell->nodes->argv[k]);
		printf("%d: %s\n", i, add[i]);
		if (!add[i])
		{
			free_env_array(add);
			return (1);
		}
		i++;
		k++;
	}
	//TODO: there's something weird happening here, a segfault.. fix it later
	add[i] = NULL;
	return (0);
}

void	ms_export(t_shell *shell)
{
	char	**add;

	add = ft_calloc(shell->nodes->argc + get_env_elements(shell->ms_envp) + 1,
			sizeof(char *));
	if (!add)
		return (perror("export: Memory allocation failed!\n"));
	if (append_envp(shell, add, 0, 1) == 1)
		return (perror("export: ft_strdup failed!\n"));
	free_env_array(shell->ms_envp);
	shell->ms_envp = add;
}
