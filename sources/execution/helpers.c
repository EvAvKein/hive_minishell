/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:21:45 by ahavu             #+#    #+#             */
/*   Updated: 2025/06/02 09:37:23 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_path(t_node *current)
{
	char	*env_path;

	env_path = env_value("PATH");
	if (!env_path)
	{
		env_path = getcwd(NULL, 0);
		if (!env_path)
		{
			print_err(current->argv[0], ": path not found in environment");
			return (NULL);
		}
	}
	return (env_path);
}

void	init_structs(t_fd *fd, t_shell *shell)
{
	t_exec	exec;

	fd->prev_fd = -2;
	fd->pipe_fd[0] = -2;
	fd->pipe_fd[1] = -2;
	ft_bzero(&exec, sizeof(t_exec));
	shell->exec = exec;
}

bool	arg_is_null(t_node *node)
{
	if (!node)
		return (true);
	if (node->argv[0][0] == '\0')
	{
		print_err(node->argv[0], ": command not found");
		get_shell()->last_exit_status = EXIT_CMD_NOT_FOUND;
		return (true);
	}
	return (false);
}

int	dup_stdout(t_shell *shell)
{
	t_node	*tmp;
	int		temp_fd;

	tmp = shell->nodes;
	temp_fd = dup(STDOUT_FILENO);
	if (temp_fd == -1)
		shell_exit(1);
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (dup2(tmp->fd, STDOUT_FILENO) == -1)
		shell_exit(1);
	return (temp_fd);
}

void	restore_stdout(int temp)
{
	if (dup2(temp, STDOUT_FILENO) == -1)
	{
		close(temp);
		shell_exit(1);
	}
	close (temp);
}
