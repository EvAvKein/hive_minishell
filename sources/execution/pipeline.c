/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:06:42 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/07 16:42:46 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_child(t_shell *shell, t_node *current, int prev_fd, int pipe_fd[2])
{
	if (current->prev && current->prev->type == INFILE)
	{
		if (handle_infile(current->prev->argv[0]) == 1)
			return ;
	}
	if (current->next && (current->next->type == OUTFILE
		|| current->next->type == APPENDFILE))
	{
		if (handle_outfiles(current) == 1)
			return ;
	}
	if (prev_fd >= 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("pipeline: dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (current->next && current->next->type == COMMAND)
	{
		if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
		{
			perror("pipeline: dup2 failed");
			exit(EXIT_FAILURE);
		}
	}
	if (is_builtin(current->argv[0]))
		execute_builtin(shell);
	else
		execute_sys_command(shell, current);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	exit(EXIT_SUCCESS);
}

static int	pipeline_parent(t_node *current, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (current->next && current->next->type == COMMAND)
	{
		close(pipe_fd[WRITE]);
		prev_fd = pipe_fd[READ];
	}
	return (prev_fd);
}

static int	do_pipe(int pipe_fd[2], int prev_fd, t_node *current, t_shell *shell)
{
	//set follow-fork-mode child
	pid_t	pid;
	
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		return (-1);
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

void	execute_pipeline(t_shell *shell)
{
	t_node	*current;
	int		prev_fd;
	int		pipe_fd[2];

	current = shell->nodes;
	prev_fd = -1;
	while (current)
	{
		if (current->type == COMMAND)
		{
			if (current->next && (current->next->type == COMMAND
			|| current->next->type == OUTFILE || current->next->type == APPENDFILE))
			{
				prev_fd = do_pipe(pipe_fd, prev_fd, current, shell);
				if (prev_fd == -1)
					return ;
			}//TODO: what if there are redirections in the middle of a pipeline?
			else
				break ;
		}
		current = current->next;
	}
	if (current && current->type == COMMAND)
		execute_last_pipeline_command(shell, current, prev_fd, pipe_fd);	
	wait_for_all_children(shell);
}
