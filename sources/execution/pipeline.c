/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:06:42 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/29 13:11:19 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_shell *shell, t_node *command)
{
	int	ret;

	if (is_builtin(command->argv[0]))
	{
		ret = (execute_builtin(shell, command));
		shell_cleanup();
		exit(ret);
	}
	else
	{
		execute_ext_command(shell, command);
		exit(EXIT_SUCCESS);
	}
}

/** The conditions on which the command line is ready to be executed:
 * the command line is given as a linked list in "sequences",
 * where INFILE node/s are at the beginning, COMMAND node/s in the middle,
 * and OUTFILE/APPENDFILE node/s at the end. The "sequence" is ready
 * to be executed when it reaches the end, ie. NULL,
 * or the start of a new "sequence".
 */

static int	ready_to_execute(t_node *current)
{
	if (!current)
		return (1);
	if ((current->type == INFILE || current->type == HEREDOC) && current->prev
		&& (current->prev->type == COMMAND
			|| current->prev->type == OUTFILE
			|| current->prev->type == APPENDFILE))
		return (1);
	if (current->type == COMMAND && current->prev
		&& (current->prev->type != INFILE && current->prev->type != HEREDOC))
		return (1);
	return (0);
}

int	execute(t_node *command, t_node *out, t_fd *fd, t_node *current)
{
	pid_t	pid;
	t_shell	*shell;

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
		if (fd->pipe_fd[WRITE] >= 0)
			close(fd->pipe_fd[WRITE]);
		fd->pipe_fd[WRITE] = out->fd;
	}
	pid = fork();
	if (parent_and_child(pid, fd, command, current) == 1)
		return (1);
	return (0);
}

int	execute_and_reset_nodes(t_node *command,
		t_node *current, t_node *out, t_fd *fd)
{
	if (command && arg_is_null(command))
		;
	else if (execute(command, out, fd, current) == 1)
	{
		command = NULL;
		out = NULL;
		return (1);
	}
	command = NULL;
	out = NULL;
	return (0);
}

void	execute_command_line(t_shell *shell, t_fd *fd)
{
	t_node	*current;
	t_node	*command;
	t_node	*out;

	command = NULL;
	out = NULL;
	current = shell->nodes;
	while (1)
	{
		if (ready_to_execute(current))
		{
			if (execute_and_reset_nodes(command, current, out, fd) == 1)
				break ;
		}
		if (!current)
			break ;
		if (current->type == INFILE || current->type == HEREDOC)
			handle_infile(fd, current);
		if (current->type == COMMAND)
			command = current;
		if (current->type == OUTFILE || current->type == APPENDFILE)
			out = current;
		current = current->next;
	}
	wait_for_all_children_and_clean_fd(shell, fd);
}
