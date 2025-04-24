/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:08:45 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/24 14:20:57 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	left_side(int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		//execute
	}
	return (pid);
}

static pid_t	right_side(int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		//execute
	}
	return (pid);
}

int	ms_pipe(t_shell *shell)
{
	int	fd[2];
	int	pid_left;
	int	pid_right;
	int	status;

	if (pipe(fd) == -1)
	{
		//TODO: error/cleanup	
	}
	pid_left = left_side(fd);
	pid_right = right_side(fd);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
}

//right now this logic only works with one single pipe, but it's a start... 