/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/24 14:20:36 by ahavu            ###   ########.fr       */
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
			printf("oops");
			//TODO: error/cleanup
	}
}

void	execution(t_shell *shell)
{
	t_node	*current;

	current = shell->nodes;
	while (current)
	{
		if (current->type == COMMAND)
			execute_command(shell);
		if (current->type == INFILE)
		{
			if (handle_infile(current->argv[0]) == 1)
				exit(EXIT_FAILURE);
		}
		if (current->type == OUTFILE)
		{
			if (handle_outfile(current->argv[0]) == 1)
				exit(EXIT_FAILURE);
		}
		if (current->type == APPENDFILE)
		{
			if (handle_appendfile(current->argv[0]) == 1)
				exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	// if there's more than one COMMAND, there will assumedly be a PIPE
}
