/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parent_and_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:26 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/19 13:19:27 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_child(t_shell *shell, t_node *command,
	t_fd *fd, t_node *current)
{
	if (fd->prev_fd != -1)
	{
		if (dup2(fd->prev_fd, STDIN_FILENO) == -1)
		{
			print_err("execution: ", "dup2 failed.");
			shell_exit(shell, 1);
		}
	}
	if (command && (current || fd->pipe_fd[WRITE] != -1))
	{
		if (dup2(fd->pipe_fd[WRITE], STDOUT_FILENO) == -1)
		{
			print_err("execution: ", "dup2 failed.");
			shell_exit(shell, 1);
		}
	}
	close_pipe(fd);
	if (command->type == COMMAND)
		execute_command(shell, command);
}

static void	pipeline_parent(t_fd *fd)
{
	if (fd->prev_fd != -1)
	{
		close(fd->prev_fd);
		fd->prev_fd = -1;
	}
	if (fd->pipe_fd[WRITE] != -1)
	{
		close(fd->pipe_fd[WRITE]);
		fd->pipe_fd[WRITE] = -1;
	}
	if (fd->pipe_fd[READ] != -1)
	{
		fd->prev_fd = fd->pipe_fd[READ];
		fd->pipe_fd[READ] = -1;
	}
}

int	parent_and_child(int pid, t_fd *fd, t_node *command, t_node *current)
{
	t_shell	*shell;

	shell = get_shell();
	if (pid == -1)
	{
		print_err("execution:", " fork failed.");
		fd_cleanup(fd);
		return (1);
	}
	if (pid == 0)
		pipeline_child(shell, command, fd, current);
	else
	{
		shell->exec.pids[shell->exec.pid_count++] = pid;
		pipeline_parent(fd);
	}
	return (0);
}
