/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/15 12:28:58 by ahavu            ###   ########.fr       */
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
		ms_env(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "cd", 2))
		return(ms_cd(shell));
	if (!ft_strncmp(shell->nodes->argv[0], "pwd", 3))
		return(ms_pwd());
	if (!ft_strncmp(shell->nodes->argv[0], "export", 6))
		return (ms_export());
	if (!ft_strncmp(shell->nodes->argv[0], "unset", 5))
		ms_unset(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "echo", 5))
		ms_echo(shell);
	if (!ft_strncmp(shell->nodes->argv[0], "exit", 4))
	{
		(void)shell;
		return(0);
	}
	return (0);
}

void	execution(t_shell *shell)
{
	pid_t	pid;
	
	shell->ms_envp = dup_envp(shell->env);
	pid = fork();
	if (pid < 0)
		printf("Error!");
	if (shell->nodes->type == COMMAND)
		execute_command(shell);
	free_env_array(shell->ms_envp);
}
