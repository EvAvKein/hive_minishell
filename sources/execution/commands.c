/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/19 15:21:31 by ahavu            ###   ########.fr       */
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
			perror("pwd: getcwd failed!");
			return (1);
		}
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

int	ms_echo(t_shell *shell)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (shell->nodes->argv[1] && shell->nodes->argv[1][0] == '-'
			&& shell->nodes->argv[1][1] == 'n')
	{
		flag = 1;
		i++;
	}
	if (flag && shell->nodes->argc == 2)
		return (0);
	if (shell->nodes->argc == 1)
	{
		printf("\n");
		return (0);
	}
	while (shell->nodes->argv[i])
	{
		//ft_putstr_fd(shell->nodes->argv[i], 1);
		printf("%s", shell->nodes->argv[i]);
		i++;
		if (i < shell->nodes->argc)
			//ft_putchar_fd(' ', 1);
			printf(" ");
	}
	if (!flag)
		//ft_putchar_fd('\n', 1);
		printf("\n");
	return (0);
}

void	ms_exit(t_shell *shell)
{
	ft_putstr_fd("exit\n", 1);
	(void)shell;
	shell_exit(shell, 0);

	//if arguments: exit status / exit with value
}
