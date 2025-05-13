/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:06:42 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/13 10:43:55 by ahavu            ###   ########.fr       */
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

// EXIT CODE 126: 

void	pipeline_child(t_shell *shell, t_node *command,
		t_fd *fd, t_node *current)
{
	if (fd->prev_fd != -1)
	{
		if (dup2(fd->prev_fd, STDIN_FILENO) == -1)
		{
			print_err("execution: ", "dup2 failed.");
			exit(EXIT_FAILURE);
		}
		//close(prev_fd);
	}
	if (command && current)
	{
		if (dup2(fd->pipe_fd[WRITE], STDOUT_FILENO) == -1)
		{
			print_err("execution: ", "dup2 failed.");
			exit(EXIT_FAILURE);
		}
	}
	close(fd->pipe_fd[READ]);
	close(fd->pipe_fd[WRITE]);
	if (command->type == COMMAND)
	{
		if (is_builtin(command->argv[0]))
			exit(execute_builtin(shell));
		else
			exit(execute_sys_command(shell, command));
	}
	exit(EXIT_SUCCESS);
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

/*static int	do_pipe(int pipe_fd[2], int prev_fd, t_node *current, t_shell *shell)
{
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
}*/

int		ready_to_execute(t_node *current)
{
	if (!current)
		return (1);
	if (current->type == INFILE && current->prev
		&& (current->prev->type == COMMAND
			|| current->prev->type == OUTFILE
			|| current->prev->type == APPENDFILE))
		return (1);
	if (current->type == COMMAND && current->prev
		&& (current->prev->type != INFILE))
		return (1);
	return (0);
}

int	execute(t_node *command, t_node *out, t_fd *fd, t_node *current)
{
	t_shell *shell;
	pid_t	pid;

	shell = get_shell();
	if (out)
		fd->pipe_fd[WRITE] = out->fd;
	else if (current) 
	{
		if (pipe(fd->pipe_fd) == -1)
		{
			print_err("execution:", " pipe failed.");
			return (1);
		}
	}
	pid = fork();
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
		shell->exec->pids[shell->exec->pid_count++] = pid;
		pipeline_parent(fd);
	}
	return (0);
}

void	execute_command_line(t_shell *shell)
{
	t_node	*current;
	t_fd	fd;
	t_node 	*command;
	t_node	*out;

	command = NULL;
	out = NULL;
	current = shell->nodes;
	fd.prev_fd = -1;
	fd.pipe_fd[0] = -1;
	fd.pipe_fd[1] = -1;
	while (1)
	{
		if (ready_to_execute(current))
		{
			if (execute(command, out, &fd, current) == 1)
			{
				command = NULL;
				out = NULL;
				break ;
			}
			command = NULL;
			out = NULL;
		}
		if (!current)
			break ;
		if (current->type == INFILE)
		{
			if (fd.prev_fd != -1)
				close(fd.prev_fd);
			fd.prev_fd = current->fd;
			current->fd = -1;
		}
		if (current->type == COMMAND)
			command = current;
		if (current->type == OUTFILE || current->type == APPENDFILE)
			out = current;
		current = current->next;
	}
	wait_for_all_children(shell);
}
