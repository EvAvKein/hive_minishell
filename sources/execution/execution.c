/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/27 09:08:47 by ahavu            ###   ########.fr       */
=======
/*   Updated: 2025/04/29 11:44:23 by ahavu            ###   ########.fr       */
>>>>>>> f7602ed4ea5edb3304f3a2c207a04b2441fd9d0e
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
<<<<<<< HEAD
	if (count_commands(shell->nodes) == 1)
		execute_command(shell);
	else
		execute_pipeline(shell);
}

		
	/*while (current)
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
}*/

=======
	int	command_count;

	command_count  = count_commands(shell->nodes);
	if (command_count == 1)
		execute_command(shell);
	else
		execute_pipeline(shell);
}
>>>>>>> f7602ed4ea5edb3304f3a2c207a04b2441fd9d0e
