/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:05:11 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/30 14:39:01 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(t_shell *shell, char *msg)
{
	if (msg)
		perror(msg);
	shell_exit(shell, EXIT_FAILURE);
}

int	get_env_elements(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
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

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "env", 3) || !ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "echo", 4)
		|| !ft_strncmp(cmd, "exit", 4))
		return (1);
	else
		return (0);
}
