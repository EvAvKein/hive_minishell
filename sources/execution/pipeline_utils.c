/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:08:39 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/27 14:49:56 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_all_children_and_clean_fd(t_shell *shell, t_fd *fd)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->exec.pid_count)
	{
		waitpid(shell->exec.pids[i], &status, 0);
		if (i == shell->exec.pid_count - 1)
		{
			if (WIFEXITED(status))
				shell->last_exit_status = WEXITSTATUS(status);
			else
				shell->last_exit_status = 1;
		}
		i++;
	}
	sigaction(SIGINT,
		&(struct sigaction){.sa_sigaction = sigint_handler}, NULL);
	fd_cleanup(fd);
}

void	fd_cleanup(t_fd *fd)
{
	if (fd->prev_fd != -1)
	{
		close(fd->prev_fd);
		fd->prev_fd = -1;
	}
	if (fd->pipe_fd[READ] != -1)
	{
		close(fd->pipe_fd[READ]);
		fd->pipe_fd[READ] = -1;
	}
	if (fd->pipe_fd[WRITE] != -1)
	{
		close(fd->pipe_fd[WRITE]);
		fd->pipe_fd[WRITE] = -1;
	}
}

void	close_pipe(t_fd *fd)
{
	if (fd->pipe_fd[READ] != -1)
	{
		close(fd->pipe_fd[READ]);
		fd->pipe_fd[READ] = -1;
	}
	if (fd->pipe_fd[WRITE] != -1)
	{
		close(fd->pipe_fd[WRITE]);
		fd->pipe_fd[WRITE] = -1;
	}
}
