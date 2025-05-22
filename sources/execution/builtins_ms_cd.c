/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ms_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:19:19 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/22 14:32:41 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_shell *shell, int i)
{
	char	*oldpwd;
	char	*pwd;

	pwd = getenv("PWD");
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (!oldpwd)
		return (1);
	free(shell->ms_envp[i]);//OTA MEIDAN OMASTA ENVPSTA PWD JA TEE SIITA OLDPWD
	shell->ms_envp[i] = oldpwd;
	//free(oldpwd);
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
	{
		free(cwd);
		return (1);
	}
	free(shell->ms_envp[i]);
	shell->ms_envp[i] = new_pwd;
	free(cwd);
	return (0);
}

static int	update_pwds(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->ms_envp[i])
	{
		if (!ft_strncmp(shell->ms_envp[i], "OLDPWD", 6))
			if (update_oldpwd(shell, i) == 1)
				return (1);
		if (!ft_strncmp(shell->ms_envp[i], "PWD=", 4))
			if (update_current_wd(shell, i) == 1)
				return (1);
		i++;
	}
	return (0);
}

char	*get_pwd_from_env(char **envp)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
		{
			ret = envp[i];
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int	ms_cd(t_shell *shell)
{
	char	*destination;

	destination = NULL;
	if (shell->nodes->argc == 1)
	{
		destination = getenv("HOME");//Eve has this function implementation
		if (!destination)
			return (1);
	}
	else
		destination = shell->nodes->argv[1];
	if (chdir(destination) != 0)
	{
		print_err("no such file or directory: ", destination);
		return (1);
	}
	if (update_pwds(shell) == 1)
		return (1);
	return (0);
}
