/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/27 14:38:22 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset(t_shell *shell)
{
	int		i;

	i = 1;
	while (shell->nodes->argv[i])
	{
		env_remove(shell->nodes->argv[i]);
		i++;
	}
	return (0);
}

int	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env)
		return (1);
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}

int	ms_pwd(char **envp)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = get_pwd_from_env(envp);
		if (!path)
		{
			print_err("pwd: ", "getcwd failed");
			return (1);
		}
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
