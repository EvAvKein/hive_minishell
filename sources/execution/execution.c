/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/13 10:25:42 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	execute_command(t_shell *shell, t_node *current)
{
	int		pid;
	int		status;

	if (is_builtin(current->argv[0]))
	{
		if (execute_builtin(shell) == 1)
		{
			shell->last_exit_status = 1;
			return (1);
		}
		shell->last_exit_status = 0;
		return (0);
	}
	pid = fork();
	if (pid == 0)
		single_command_child(shell, current);
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			shell->last_exit_status = 1;
		}
		else
			shell->last_exit_status = WEXITSTATUS(status);
	}
	else if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	return (0);
}*/

int	count_commands(t_node *head)
{
	t_node	*tmp;
	int		count;
	
	tmp = head;
	count = 0;
	while (tmp->next && tmp->next != head)
	{
		if (tmp->type == COMMAND)
			count++;
		tmp = tmp->next;
	}
	if (tmp->type == COMMAND)
		count++;
	return (count);
}

int	open_redirections(t_shell *shell)
{
	t_node *node;

	node = shell->nodes;
	while (node)
	{
		if (node->type == INFILE
			|| node->type == OUTFILE || node->type == APPENDFILE)
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
    t_exec    *exec;

	exec = ft_calloc(1, sizeof(t_exec));
	shell->exec = exec;
	if (open_redirections(shell) == 1)
		return ;
	execute_command_line(shell);
}
