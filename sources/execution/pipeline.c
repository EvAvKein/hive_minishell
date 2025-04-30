/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:06:42 by ahavu             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/27 09:07:14 by ahavu            ###   ########.fr       */
=======
/*   Updated: 2025/04/29 11:44:34 by ahavu            ###   ########.fr       */
>>>>>>> f7602ed4ea5edb3304f3a2c207a04b2441fd9d0e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	execute_pipeline(t_shell *shell)
{
	
}
=======
static void	pipeline_child(t_shell *shell, t_node *current, int prev_fd, int pipe_fd[2])
{
	if (prev_fd > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (apply_redirections(current))
		exit(EXIT_SUCCESS);
	if (current->next && current->next->type == COMMAND)
		dup2(pipe_fd[1], STDOUT_FILENO); // redirect the fd
	close(pipe_fd[1]);//close the WRITE end of the pipe because it's been redirected
	close(pipe_fd[0]);// close the READ end of the pipe (because it's unused)
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
		prev_fd = pipeline_parent(current, prev_fd, pipe_fd);
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
			if (current->next && current->next->type == COMMAND)
			{
				prev_fd = do_pipe(pipe_fd, prev_fd, current, shell);
			}
		}
		current = current->next;
	}
	//wait for all children - just wait() and compare the pids?
}
>>>>>>> f7602ed4ea5edb3304f3a2c207a04b2441fd9d0e
