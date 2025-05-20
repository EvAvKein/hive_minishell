/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/20 13:53:16 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_builtin(t_shell *shell, int temp)
{
	if (count_redirections(shell) > 0)
	{
		temp = dup(STDOUT_FILENO);
		if (temp == -1)
			shell_exit(shell, 1);
		if (dup2(shell->nodes->next->fd, STDOUT_FILENO) == -1)
			shell_exit(shell, 1);
	}
	if (execute_builtin(shell) == 1)
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

	shell->working_dir = getcwd(NULL, 0);
	fd.prev_fd = -1;
	fd.pipe_fd[0] = -1;
	fd.pipe_fd[1] = -1;
	temp = -1;
	ft_bzero(&exec, sizeof(t_exec));
	shell->exec = exec;
	command_count = count_commands(shell);
	if (open_redirections(shell) == 1)
		return ;
	if (command_count == 1 && is_builtin(shell->nodes->argv[0]))
	{
		handle_single_builtin(shell, temp);
		return ;
	}
	execute_command_line(shell, &fd);
}
