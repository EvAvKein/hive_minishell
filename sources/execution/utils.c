/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:05:11 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/21 13:23:39 by ahavu            ###   ########.fr       */
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

int	count_commands(t_shell *shell)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = shell->nodes;
	while (tmp)
	{
		if (tmp->type == COMMAND)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
