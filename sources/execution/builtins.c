/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/21 15:48:42 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->ms_envp[i])
	{
		if (ft_strchr(shell->ms_envp[i], '='))
			printf("%s\n", shell->ms_envp[i]);
		i++;
	}
	return (0);
}

int	ms_pwd(char **envp)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = get_pwd_from_env(envp);
		if (!path)
		{
			print_err("pwd: ", "getcwd failed");
			return (1);
		}
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

static int	check_flag(t_shell *shell)
{
	if (shell->nodes->argv[1] && shell->nodes->argv[1][0] == '-'
		&& shell->nodes->argv[1][1] && shell->nodes->argv[1][1] == 'n')
		return (1);
	else
		return (0);
}

int	ms_echo(t_shell *shell)
{
	int	i;
	int	flag;

	i = 1;
	flag = check_flag(shell);
	if (flag)
		i++;
	if (flag && shell->nodes->argc == 2)
	{
		shell_cleanup(shell);
		return (0);
	}
	if (shell->nodes->argc == 1)
	{
		printf("\n");
		shell_cleanup(shell);
		return (0);
	}
	while (shell->nodes->argv[i])
	{
		printf("%s", shell->nodes->argv[i]);
		i++;
		if (i < shell->nodes->argc)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	if (shell->exec.child_process)//TODO: this doesn't work
	{
		printf("cleaning child proc\n");
		shell_cleanup(shell);
	}
	return (0);
}

void	ms_exit(t_shell *shell)
{
	if (shell->nodes->argc > 1)
		printf("exit\n");
	if (shell->nodes->argv[1])
		shell->last_exit_status = ft_atoi(shell->nodes->argv[1]);
	shell_exit(shell, 0);
}
