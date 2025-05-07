/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:06:42 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/12 13:30:31 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirections(t_node *current)
{
	int	ret;
//  this should probably happen in a while loop in case of several infiles/outfiles
	ret = 0;
	if (current->prev && current->prev->type == INFILE)
		ret = handle_infile(current);
	if (current->next && current->next->type == OUTFILE)
		ret = handle_outfile(current);
	if (current->next && current->next->type == APPENDFILE)
		ret = handle_appendfile(current);
	return (ret);
}

void	pipeline_child(t_shell *shell, t_node *current,
		int prev_fd, int pipe_fd[2])
{
	//if (check_redirections(current) == 1)
	//	exit(EXIT_FAILURE);
	if (prev_fd >= 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("pipeline: dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (current->next)
	{
		if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
		{
			perror("pipeline: dup2 failed");
			exit(EXIT_FAILURE);
		}
	}
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	if (current->type == COMMAND)
	{
		if (is_builtin(current->argv[0]))
			execute_builtin(shell);
		else
			execute_sys_command(shell, current);
	}
	exit(EXIT_SUCCESS);
}

static int	pipeline_parent(t_node *current, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (current->next)
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
			prev_fd = do_pipe(pipe_fd, prev_fd, current, shell);
			if (prev_fd == -1)
				return ;
		}
		current = current->next;
	}
	wait_for_all_children(shell);
}
