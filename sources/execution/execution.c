/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/27 14:56:55 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_builtin(t_shell *shell, int temp)
{
	t_node	*tmp;
	t_node	*cmd;

	cmd = NULL;
	if (count_outfiles(shell) > 0)
		temp = dup_stdout(shell);
	tmp = shell->nodes;
	while (tmp)
	{
		if (tmp->type == COMMAND)
		{
			cmd = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	if (execute_builtin(shell, cmd) == 1)
	{
		shell->last_exit_status = 1;
		command_cleanup(shell);
	}
	else
		shell->last_exit_status = 0;
	if (temp != -1)
		restore_stdout(temp);
}

void	execution(t_shell *shell)
{
	int			command_count;
	t_fd		fd;
	int			temp;

	temp = -1;
	ft_bzero(&fd, sizeof(t_fd));
	init_structs(&fd, shell);
	command_count = count_commands(shell);
	if (command_count >= MAX_CMDS)
	{
		print_err("too many commands", ".");
		return ;
	}
	if (open_redirections(shell) == 1)
		return ;
	if (is_builtin_in_parent(shell->nodes))
	{
		handle_single_builtin(shell, temp);
		return ;
	}
	if (command_count >= 1)
		execute_command_line(shell, &fd);
}
