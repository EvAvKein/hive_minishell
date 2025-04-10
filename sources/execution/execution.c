/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/10 17:01:48 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_command(t_shell *shell)
{
	char	*path;
	if (ft_strchr(shell->nodes->argv, '/'))
		//that's the path and the executable
	else
	   path = getenv(shell->nodes->argv);
    execve(path, shell->nodes->argv, shell->env);
}

void	execution(t_shell *shell)
{
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
		//error
	if (shell->nodes->type == COMMAND)
		execute_command(shell->nodes);
	if (shell->nodes->type == HEREDOC)
	if (shell->nodes->type == INFILE)
	if (shell->nodes->type == OUTFILE)
	if (shell->nodes->type == APPENDFILE)
}
