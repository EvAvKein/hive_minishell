/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:31:12 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/17 14:40:46 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_shell *shell)
{
	int	pid;
	
	if (is_builtin(shell->nodes->argv[0]))
			execute_builtin(shell);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execute_sys_command(shell) == 1)
			{
				perror("execution failed");
				exit(EXIT_FAILURE);
			}
		}
		if (pid > 0)
		{
			if (waitpid(pid, NULL, 0) == -1)
			{
				perror("waitpid failed");
				exit(EXIT_FAILURE);
			}
		}
		else
			perror("fork failed");
	}
}
