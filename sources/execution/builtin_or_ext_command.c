/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_ext_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:31:12 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/22 14:47:28 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*iterate_through_path_list(char **path_list, t_node *current)
{
	int		i;
	char	*ret_path;
	char	*temp;

	i = 0;
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		if (!temp)
		{
			print_err(current->argv[0], ": ft_strjoin failed");
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
	return (ret_path);
}

static char	*get_path_from_envp(t_node *current)
{
	char	*env_path;
	char	*ret_path;
	char	**path_list;

	env_path = getenv("PATH");//TODO: make your on getenv() for ms_envp
	if (!env_path)
	{
		print_err(current->argv[0], ": path not found in environment");
		return (NULL);
	}
	path_list = ft_split(env_path, ':');
	if (!path_list)
	{
		print_err(current->argv[0], ": ft_split failed");
		return (NULL);
	}
	ret_path = iterate_through_path_list(path_list, current);
	free_env_array(path_list);
	if (!ret_path)
		print_err(current->argv[0], ": command not found");
	return (ret_path);
}

static char	*get_path_from_arg(char *command)
{
	char	*path;

	path = command;
	if (access(path, F_OK) != 0)
	{
		print_err(command, ": invalid path");
		path = NULL;
	}
	return (path);
}

void	execute_ext_command(t_shell *shell, t_node *current)
{
	char	*path;
	char	**args;
	char	**tmp_envp;

	if (ft_strchr(current->argv[0], '/')) //TODO: access X_OK instead
		path = get_path_from_arg(current->argv[0]);
	else
		path = get_path_from_envp(current);
	if (!path)
		shell_exit(shell, 127);
	args = current->argv;
	current->argv = NULL;
	tmp_envp = shell->ms_envp;
	shell->ms_envp = NULL;
	shell_cleanup(shell);
	execve(path, args, tmp_envp);
	if (path && path != args[0])
		free(path);
	free_env_array(args);
	print_err("execution: ", strerror(errno));
	shell_exit(shell, 126);
}

int	execute_builtin(t_shell *shell, t_node *command)
{
	if (!ft_strncmp(command->argv[0], "env", 4))
		return (ms_env(shell));
	else if (!ft_strncmp(command->argv[0], "cd", 3))
		return (ms_cd(shell));
	else if (!ft_strncmp(command->argv[0], "pwd", 4))
		return (ms_pwd(shell->ms_envp));
	else if (!ft_strncmp(command->argv[0], "export", 7))
		return (ms_export(shell));
	else if (!ft_strncmp(command->argv[0], "unset", 6))
		return (ms_unset(shell));
	else if (!ft_strncmp(command->argv[0], "echo", 5))
		return (ms_echo(shell, command));
	else if (!ft_strncmp(command->argv[0], "exit", 5))
		(ms_exit(shell));
	return (0);
}
