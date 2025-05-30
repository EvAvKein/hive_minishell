/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ms_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:19:19 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/30 09:50:28 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_shell *shell, int i)
{
	char	*oldpwd;
	char	*pwd;

	pwd = env_value("PWD");
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (!oldpwd)
		return (1);
	free(shell->env[i]);
	shell->env[i] = oldpwd;
	return (0);
}

static int	update_current_wd(t_shell *shell, int i)
{
	char	*cwd;
	char	*new_pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	if (shell->working_dir)
		free(shell->working_dir);
	shell->working_dir = cwd;
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return (1);
	free(shell->env[i]);
	shell->env[i] = new_pwd;
	return (0);
}

static int	update_pwds(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "OLDPWD", 6))
		{
			if ((!shell->env[i][6] || shell->env[i][6] == '=')
				&& update_oldpwd(shell, i) != 0)
				return (1);
		}
		if (!ft_strncmp(shell->env[i], "PWD", 3))
		{
			if ((!shell->env[i][3] || shell->env[i][3] == '=')
			&& update_current_wd(shell, i) != 0)
				return (1);
		}
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
		if (!ft_strncmp(envp[i], "PWD", 3))
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
		destination = env_value("HOME");
		if (!destination)
		{
			print_err("cd: ", "HOME not set");
			return (1);
		}
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
