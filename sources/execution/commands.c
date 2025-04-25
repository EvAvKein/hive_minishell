/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/24 14:10:46 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->ms_envp[i])
	{
		if (ft_strchr(shell->ms_envp[i], '='))
			printf("%s\n", shell->ms_envp[i]);
		i++;
	}
}

void	ms_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd: getcwd failed!");
		return ;
	}
	printf("%s\n", path);
	free(path);
}

void	ms_echo(t_shell *shell)
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
		return ;
	if (shell->nodes->argc == 1)
		return (ft_putchar_fd('\n', 1));
	while (shell->nodes->argv[i])
	{
		ft_putstr_fd(shell->nodes->argv[i], 1);
		i++;
		if (i < shell->nodes->argc)
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}

void	ms_exit(t_shell *shell)
{
	free_env_array(shell->ms_envp);
	(void)shell;
	exit(EXIT_SUCCESS);
}
