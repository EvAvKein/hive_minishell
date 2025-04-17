/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/17 14:41:38 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_sys_command(t_shell *shell)
{
	char	*path;
	char	**path_list;
	int		i;
	
	i = 0;
	path_list = NULL;
	if (ft_strchr(shell->nodes->argv[0], '/'))
	{
		path = shell->nodes->argv[0];
		if (access(path, F_OK) != 0)
			path = NULL;
	}
	else
	{
		path = getenv("PATH");
		if (!path)
			printf("TODO");
		path_list = ft_split(path, ':');
		path = NULL;
	   	while (path_list[i])
	   	{
			path = ft_strjoin(path_list[i], "/");
			path = ft_strjoin(path, shell->nodes->argv[0]);
			if (!path)
			{
				perror("executable: ft_strjoin failed\n");
				return (1);
			}
			if (access(path, F_OK) == 0)
				break ;
			i++;
			path = NULL;
	   	}
	}
	if (!path)
	{
		perror("executable or path doesn't exist\n");
		return (1);
	}
    execve(path, shell->nodes->argv, shell->env);
	free_env_array(path_list);
	free(path);
	return (0);
}

int	execute_builtin(t_shell *shell)
{
	if (!ft_strncmp(shell->nodes->argv[0], "env", 3))
		ms_env(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "cd", 2))
		ms_cd(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "pwd", 3))
		ms_pwd();
	if (!ft_strncmp(shell->nodes->argv[0], "export", 6))
		ms_export(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "unset", 5))
		ms_unset(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "echo", 5))
		ms_echo(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "exit", 4))
		ms_exit(shell);
	return (0);
}

void	execution(t_shell *shell)
{
	pid_t	pid;
	
	if (shell->nodes->type == COMMAND)
		execute_command(shell);
}
