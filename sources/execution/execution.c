/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/22 13:33:48 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_builtin(t_shell *shell, int temp)
{
	t_node	*tmp;
	
	if (count_outfiles(shell) > 0)
	{
		tmp = shell->nodes;
		temp = dup(STDOUT_FILENO);
		if (temp == -1)
			shell_exit(shell, 1);
		while (tmp)
		{
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
		if (dup2(tmp->fd, STDOUT_FILENO) == -1)
			shell_exit(shell, 1);
	}
	if (execute_builtin(shell, shell->nodes) == 1)
	{
		shell->last_exit_status = 1;
		command_cleanup(shell);
	}
	else
		shell->last_exit_status = 0;
	if (temp != -1)
	{
		if (dup2(temp, STDOUT_FILENO) == -1)
		{
			close(temp);
			shell_exit(shell, 1);
		}
		close (temp);
	}
}

void	execution(t_shell *shell)
{
	t_exec		exec;
	int			command_count;
	t_fd		fd;
	int			temp;

	fd.prev_fd = -1;
	fd.pipe_fd[0] = -1;
	fd.pipe_fd[1] = -1;
	temp = -1;
	ft_bzero(&exec, sizeof(t_exec));
	shell->exec = exec;
	command_count = count_commands(shell);
	if (command_count >= MAX_CMDS)
	{
		print_err("too many commands", ".");
		return ;
	}
	if (open_redirections(shell) == 1)
		return ;
	if (command_count == 1 && is_builtin(shell->nodes->argv[0]))
	{
		handle_single_builtin(shell, temp);
		return ;
	}
	execute_command_line(shell, &fd);
}
