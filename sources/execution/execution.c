/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/29 11:44:23 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_shell *shell)
{
	if (is_builtin(shell->nodes->argv[0]))
	{
		execute_builtin(shell);
		shell->last_exit_status = 0;
	}
	else
	{
		if (fork_and_execute_sys_command(shell) == 1)
			perror("fork failed");
	}
}

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

void	execution(t_shell *shell)
{
	int	command_count;

	command_count  = count_commands(shell->nodes);
	if (command_count == 1)
		execute_command(shell);
	else
		execute_pipeline(shell);
}
