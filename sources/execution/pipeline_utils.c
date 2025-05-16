/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:08:39 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/16 12:37:20 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_all_children(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->exec->pid_count)
	{
		waitpid(shell->exec->pids[i], &status, 0);
		if (i == shell->exec->pid_count - 1)
		{
			if (WIFEXITED(status)) // child process exited normally
				shell->last_exit_status = WEXITSTATUS(status);
			else // child process was terminated by signal or error
				shell->last_exit_status = 1;
		}
		i++;
	}
}

