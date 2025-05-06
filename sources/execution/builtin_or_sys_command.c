/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_sys_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:31:12 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/07 12:45:48 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_from_envp(t_node *current)
{
	char	*env_path;
	char	*ret_path;
	char	*temp;
	char	**path_list;
	int		i;

	i = 0;
	env_path = getenv("PATH");
	if (!env_path)
	{
		perror("path not found in environment");
		return (NULL);
	}
	path_list = ft_split(env_path, ':');
	if (!path_list)
	{
		perror("ft_split failed");
		return (NULL);
	}
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		if (!temp)
		{
			perror("ft_strjoin failed");
			return (NULL);
		}
		ret_path = ft_strjoin(temp, current->argv[0]);
		free(temp);
		if (!ret_path)
			break ;
		if (access(ret_path, F_OK) == 0)
			break ;
		free(ret_path);
		ret_path = NULL;
		i++;
	}
	free_env_array(path_list);
	if (!ret_path)
		perror("command not found/invalid path");
	return (ret_path);
}

static char	*get_path_from_arg(char *command)
{
	char	*path;

	path = command;
	if (access(path, F_OK) != 0)
	{
		perror("invalid path");
		path = NULL;
	}
	return (path);
}

int	execute_sys_command(t_shell *shell, t_node *current)
{
	char	*path;
	char	**path_list;

	path_list = NULL;
	if (ft_strchr(current->argv[0], '/'))
		path = get_path_from_arg(current->argv[0]);
	else
		path = get_path_from_envp(current);
	if (!path)
		return (1);
	if (execve(path, current->argv, shell->ms_envp) == -1)
		perror("execve failed");
	if (path_list)
		free_env_array(path_list);
	if (path && path != current->argv[0])
		free(path);
	return (0);
}

int	fork_and_execute_sys_command(t_shell *shell)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (execute_sys_command(shell, shell->nodes) == 1)
			exit(1);
	}
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			shell->last_exit_status = 1;
		}
		else
			shell->last_exit_status = WEXITSTATUS(status);
			//TODO: store all the other exit statuses as well!! from all COMMANDS
	}
	else if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	return (0);
}

int	execute_builtin(t_shell *shell)
{
	if (!ft_strncmp(shell->nodes->argv[0], "env", 4))
		ms_env(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "cd", 3))
		if (ms_cd(shell) == 1)
			perror("cd failed");
	if (!ft_strncmp(shell->nodes->argv[0], "pwd", 4))
		ms_pwd(shell->ms_envp);
	if (!ft_strncmp(shell->nodes->argv[0], "export", 7))
		ms_export(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "unset", 6))
		ms_unset(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "echo", 5))
		ms_echo(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "exit", 5))
		ms_exit(shell);
	return (0);
}
