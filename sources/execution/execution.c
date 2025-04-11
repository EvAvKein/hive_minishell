/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/11 14:53:09 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_shell *shell)
{
	/*char	*path;
	if (ft_strchr(shell->nodes->argv, '/'))
		//that's the path and the executable
	else
	   path = getenv(shell->nodes->argv);
    execve(path, shell->nodes->argv, shell->env);*/
	if (!ft_strncmp(shell->nodes->argv[0], "env", 3))
		return (ms_env(shell->env));
	if (!ft_strncmp(shell->nodes->argv[0], "cd", 2))
		return(ms_cd());
	if (!ft_strncmp(shell->nodes->argv[0], "pwd", 3))
		return(ms_pwd());
	if (!ft_strncmp(shell->nodes->argv[0], "export", 6))
		return (ms_export());
	if (!ft_strncmp(shell->nodes->argv[0], "unset", 5))
		return (ms_unset(shell));
	if (!ft_strncmp(shell->nodes->argv[0], "exit", 4))
	{
		(void)shell;
		//TODO: clean up
		return(0);
	}
}

void	execution(t_shell *shell)
{
	pid_t	pid;
	
	//pid = fork();
	//if (pid < 0)
		//error
	if (shell->nodes->type == COMMAND)
		execute_command(shell->nodes);
	if (shell->nodes->type == HEREDOC)
	if (shell->nodes->type == INFILE)
	if (shell->nodes->type == OUTFILE)
	if (shell->nodes->type == APPENDFILE)
}
