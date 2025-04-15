/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ms_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:19:19 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/15 16:12:23 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwds(t_shell *shell, char *oldpwd)
{
	int		i;
	char	*cwd;

	i = 0;
	while(shell->ms_envp[i])
	{
		if (!ft_strncmp(shell->ms_envp[i], "OLDPWD=", 7))
		{
			free(shell->ms_envp[i]);
			shell->ms_envp[i] = ft_strjoin("OLDPWD=", oldpwd);
			if (!shell->ms_envp[i])
				return (1);
		}
		if (!ft_strncmp(shell->ms_envp[i], "PWD=", 4))
		{
			cwd = getcwd(NULL, 0);
			free(shell->ms_envp[i]);
			shell->ms_envp[i] = ft_strjoin("PWD=", cwd);
			if (!shell->ms_envp[i])
				return (1);
		}
		i++;
	}
	free(cwd);
	return (0);
}

void	ms_cd(t_shell *shell)
{
	char	*oldpwd;
	char	*destination;

	destination = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd: getcwd failed!\n"));
	if(!shell->nodes->argv[1])
	{
		destination = getenv("HOME");
		if (!destination)
			return(perror("cd: getenv failed!\n"));
	}
	else
		destination = shell->nodes->argv[1];
	if (chdir(destination) != 0)
		return (perror("cd: chdir failed!\n"));
	if (update_pwds(shell, oldpwd) == 1);
		return (perror("cd: ft_strjoin failed!\n"));
}

