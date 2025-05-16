/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:06:42 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/16 14:25:16 by ahavu            ###   ########.fr       */
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
	close(fd->pipe_fd[READ]);
	close(fd->pipe_fd[WRITE]);
	if (command->type == COMMAND)
	{
		if (is_builtin(command->argv[0]))
			exit(execute_builtin(shell));
		else
		{
			execute_sys_command(shell, command);
			exit(EXIT_SUCCESS);
		}
	}
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

/** The conditions on which the command line is ready to be executed:
 * the command line is given as a linked list in "sequences", where INFILE node/s
 * are at the beginning, COMMAND node/s in the middle, and OUTFILE/APPENDFILE node/s at the end.
 * The "sequence" is ready to be executed when it reaches the end, ie. NULL, or the start of a new "sequence".
 */

static int		ready_to_execute(t_node *current)
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
	if (current)
	{
		if (pipe(fd->pipe_fd) == -1)
		{
			print_err("execution:", " pipe failed.");
			return (1);
		}
	}
	if (out)
	{
		if (fd->pipe_fd[WRITE] != 1)
			close(fd->pipe_fd[WRITE]);
		fd->pipe_fd[WRITE] = out->fd;
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

void	execute_command_line(t_shell *shell, t_fd *fd)
{
	t_node	*current;
	t_node 	*command;
	t_node	*out;

	command = NULL;
	out = NULL;
	current = shell->nodes;
	while (1)
	{
		if (ready_to_execute(current))
		{
			if (execute(command, out, fd, current) == 1)
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
			if (fd->prev_fd != -1)
				close(fd->prev_fd);
			fd->prev_fd = current->fd;
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
