/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parent_and_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:26 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/23 11:09:30 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_child(t_shell *shell, t_node *command,
	t_fd *fd, t_node *current)
{
	shell->exec.child_process = true;
	if (fd->prev_fd != -1)
	{
		if (dup2(fd->prev_fd, STDIN_FILENO) == -1)
		{
			print_err("execution: ", "dup2 failed.");
			shell_exit(1);
		}
	}
	if (command && (current || fd->pipe_fd[WRITE] != -1))
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
	else
		shell_cleanup(shell);
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
	{
		sigaction(SIGINT,
			&(struct sigaction){.sa_handler = SIG_DFL}, NULL);
		sigaction(SIGPIPE,
			&(struct sigaction){.sa_sigaction = sigpipe_handler}, NULL);
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
