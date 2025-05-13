/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/16 12:53:43 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_infile(t_shell *shell, t_node *node)
{
	if (access(node->argv[0], F_OK) == -1)
	{
		shell->last_exit_status = 2;
		print_err(node->argv[0], " file doesn't exist");
		return (1);
	}
	node->fd = open(node->argv[0], O_RDONLY);
	if (node->fd == -1)
	{
		print_err(node->argv[0], " couldn't be read.");
		return (1);
	}
	return (0);
}

static int	open_outfile_or_appendfile(t_node *node, t_shell *shell)
{
	if (node->type == OUTFILE)
	{
		node->fd = open(node->argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (node->fd == -1)
		{
			shell->last_exit_status = 2;
			print_err(node->argv[0], " couldn't be read.");
			return (1);
		}
	}
	if (node->type == APPENDFILE)
	{
		node->fd = open(node->argv[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (node->fd == -1)
		{
			shell->last_exit_status = 2;
			print_err(node->argv[0], " couldn't be read.");
			return (1);
		}
	}
	return (0);
}

int	open_redirections(t_shell *shell)
{
	t_node *node;

	node = shell->nodes;
	while (node)
	{
		if (node->type == INFILE)
		{
			if (open_infile(shell, node) == 1)
				return (1);
		}
		if (node->type == OUTFILE || node->type == APPENDFILE)
		{
			if (open_outfile_or_appendfile(node, shell) == 1)
				return (1);
		}
		node = node->next;
	}
	
	return (0);
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

void    execution(t_shell *shell)
{
    t_exec		*exec;
	int			command_count;
	t_fd		fd;

	fd.prev_fd = -1;
	fd.pipe_fd[0] = -1;
	fd.pipe_fd[1] = -1;
	exec = ft_calloc(1, sizeof(t_exec));
	shell->exec = exec;
	command_count = count_commands(shell);
	if (open_redirections(shell) == 1)
		return ;
	if (command_count == 1 && is_builtin(shell->nodes->argv[0]))
	{
		execute_builtin(shell);
		return ;
	}
	execute_command_line(shell, &fd);
}
