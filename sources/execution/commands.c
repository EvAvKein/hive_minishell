/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/16 14:31:20 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	while(shell->ms_envp[i])
	{
		if (ft_strchr(shell->ms_envp[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
}

void	ms_pwd(void)
{
	char	*path;
	
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror(RED"pwd: getcwd failed!\n"RESET);
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
	if (shell->nodes->argv[1][0] == '-' && shell->nodes->argv[1][1] == 'n')
	{
		flag = 1;
		i++;
	}
	if (flag && shell->nodes->argc == 2)
		return ;
	while(shell->nodes->argv[i])
	{
		ft_putstr_fd(shell->nodes->argv[i], 1);
		i++;
		if (i < shell->nodes->argc)
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
int	check_removables(char *line, char **remove)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_strchr(argv[i], '\n'))
	{
		flag = 1;
		i++;
	}
	while(argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
	}
	if (flag)
		ft_putchar_fd('\n', 1);
}
