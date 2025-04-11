/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/16 14:28:51 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	execute_command(t_shell *shell)
{
	char	*path;
	//if (ft_strchr(shell->nodes->argv, '/'))
		//that's the path and the executable
	//else
	   path = getenv(shell->nodes->argv);
    execve(path, shell->nodes->argv, shell->env);
}*/

int	execute_builtin(t_shell *shell)
{
	if (!ft_strncmp(shell->nodes->argv[0], "env", 3))
		ms_env(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "cd", 2))
		ms_cd(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "pwd", 3))
		ms_pwd();
	if (!ft_strncmp(shell->nodes->argv[0], "export", 6))
		ms_export(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "unset", 5))
		ms_unset(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "echo", 5))
		ms_echo(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "exit", 4))
	{
		(void)shell;
		//TODO:cleanup
		exit(EXIT_SUCCESS);
		return(0);
	}
	return (0);
}

void	execution(t_shell *shell)
{
	shell->ms_envp = dup_envp(shell->env);
	if(!shell->ms_envp)
		return (exit(EXIT_FAILURE));
	if (shell->nodes->type == COMMAND)
	{
		if (is_builtin(shell->nodes->argv[0]))
			execute_builtin(shell);	
	}
	free_env_array(shell->ms_envp);
}
