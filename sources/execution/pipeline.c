/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:06:42 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/07 12:39:28 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_child(t_shell *shell, t_node *current, int prev_fd, int pipe_fd[2])
{
	if (prev_fd >= 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("pipeline: dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (apply_redirections(current))
		exit(EXIT_SUCCESS);
	if (current->next && current->next->type == COMMAND)
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) // redirect the fd
		{
			perror("pipeline: dup2 failed");
			exit(EXIT_FAILURE);
		}
	pipe_fd = close_pipe_fds(pipe_fd);
	if (is_builtin(current->argv[0]))
		execute_builtin(shell);
	else
		execute_sys_command(shell);
	exit(EXIT_SUCCESS);
}

static int	pipeline_parent(t_node *current, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (current->next && current->next->type == COMMAND)
	{
		close(pipe_fd[1]); // close the WRITE end of the pipe
		prev_fd = pipe_fd[0];
	}
	return (prev_fd);
}

static int	do_pipe(int pipe_fd[2], int prev_fd, t_node *current, t_shell *shell)
{
	pid_t	pid;
	
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (pid == 0)
		pipeline_child(shell, current, prev_fd, pipe_fd);
	else
	{
		shell->exec->pids[shell->exec->pid_count++] = pid;
		prev_fd = pipeline_parent(current, prev_fd, pipe_fd);
	}
	return (prev_fd);
}

int	execute_pipeline(t_shell *shell)
{
	t_node	*current;
	int		prev_fd;
	int		pipe_fd[2];

	current = shell->nodes;
	prev_fd = -1;
	while (current) //loop through the first commands
	{
		if (current->type == COMMAND)
		{
			if (current->next && current->next->type == COMMAND)
				prev_fd = do_pipe(pipe_fd, prev_fd, current, shell);
			else
				break ;
		}
		current = current->next;
	}
	if (current && current->type == COMMAND) // execute the last command
		execute_last_pipeline_command(shell, current, prev_fd, pipe_fd);
	wait_for_all_children(shell);
	return (0);
}
