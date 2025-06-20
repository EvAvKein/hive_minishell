/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parent_and_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:26 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/30 12:39:52 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_child(t_shell *shell, t_node *command,
	t_fd *fd, t_node *current)
{
	if (fd->prev_fd == -1 || fd->pipe_fd[WRITE] == -1)
	{
		fd_cleanup(fd);
		shell_exit(1);
	}
	if (fd->prev_fd >= 0)
	{
		if (dup2(fd->prev_fd, STDIN_FILENO) == -1)
		{
			print_err("execution: ", "dup2 failed.");
			shell_exit(1);
		}
	}
	if (command && (current || fd->pipe_fd[WRITE] != -2))
	{
		if (dup2(fd->pipe_fd[WRITE], STDOUT_FILENO) == -1)
		{
			print_err("execution: ", "dup2 failed.");
			shell_exit(1);
		}
	}
	fd_cleanup(fd);
	if (command && command->type == COMMAND)
		execute_command(shell, command);
	shell_cleanup();
}

static void	pipeline_parent(t_fd *fd)
{
	if (fd->prev_fd >= 0)
	{
		close(fd->prev_fd);
		fd->prev_fd = -2;
	}
	if (fd->pipe_fd[WRITE] >= 0)
	{
		close(fd->pipe_fd[WRITE]);
		fd->pipe_fd[WRITE] = -2;
	}
	if (fd->pipe_fd[READ] >= 0)
	{
		fd->prev_fd = fd->pipe_fd[READ];
		fd->pipe_fd[READ] = -2;
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
	{
		set_child_signal_handlers();
		pipeline_child(shell, command, fd, current);
	}
	else
	{
		shell->exec.pids[shell->exec.pid_count++] = pid;
		sigaction(SIGINT,
			&(struct sigaction){.sa_handler = SIG_IGN}, NULL);
		pipeline_parent(fd);
	}
	return (0);
}
