/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ms_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:19:19 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/30 11:31:14 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_shell *shell, char *oldpwd, int i)
{
	char	*new_oldpwd;
	
	new_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	if (!new_oldpwd)
		return (1);
	free(shell->ms_envp[i]);
	shell->ms_envp[i] = new_oldpwd;
	return (0);
}

static int	update_current_wd(t_shell *shell, int i)
{
	char	*cwd;
	char	*new_pwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return (1);
	free(shell->ms_envp[i]);
	shell->ms_envp[i] = new_pwd;
	return (0);
}

static int	update_pwds(t_shell *shell, char *oldpwd)
{
	int		i;

	i = 0;
	while (shell->ms_envp[i])
	{
		if (!ft_strncmp(shell->ms_envp[i], "OLDPWD", 6))
			if (update_oldpwd(shell, oldpwd, i) == 1)
				return (1);
		if (!ft_strncmp(shell->ms_envp[i], "PWD=", 4))
			if (update_current_wd(shell, i) == 1)
				return (1);
		i++;
	}
	return (0);
}

int	ms_cd(t_shell *shell)
{
	char	*oldpwd;
	char	*destination;

	destination = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (!shell->nodes->argv[1])
	{
		destination = getenv("HOME");
		if (!destination)
			return (1);
	}
	else
		destination = shell->nodes->argv[1];
	if (chdir(destination) != 0)
		return (1);
	if (update_pwds(shell, oldpwd) == 1)
		return (1);
	free(oldpwd);
	return (0);
}
