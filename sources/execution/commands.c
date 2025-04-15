/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/15 12:24:13 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	shell->ms_envp = ft_calloc(get_env_elements(shell->env), sizeof(char *));
	if (!shell->ms_envp)
	{
		shell->ms_envp = NULL;
		perror("env: Memory allocation failed!\n");
		return ;
	}
	while(shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
		{
			shell->ms_envp[i] = shell->env[i];
			printf("%s\n", shell->env[i]);
		}
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

void	ms_echo(int argc, char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argv[1][0] == '-' && argv[1][1] == 'n')
	{
		flag = 1;
		i++;
	}
	if (flag && argc == 2)
		return ;
	while(argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (i < argc)
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
