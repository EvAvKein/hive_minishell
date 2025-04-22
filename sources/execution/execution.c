/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/22 15:28:27 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_shell *shell)
{
	int	status;
	
	if (is_builtin(shell->nodes->argv[0]))
	{
		execute_builtin(shell);
		shell->last_exit_status = 0;
	}
	else
	{
		if (fork_and_execute_sys_command(shell) == 1)
			//TODO: error/cleanup
	}
}

void	execution(t_shell *shell)
{
	t_node	*current;

	current = shell->nodes;
	while (current)
	{
		current = current->next;
	}
	if (shell->nodes->type == COMMAND)
		execute_command(shell);
}
