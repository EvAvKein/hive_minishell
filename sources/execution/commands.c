/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/14 11:43:05 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	shell->env_dup = ft_calloc(get_env_elements(shell->env), sizeof(char *));
		if (!shell->env_dup)
			//error TODO
	while(shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
		{
			shell->env_dup[i] = shell->env[i];
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
		//error - TODO
	printf("%s\n", path);
	free(path);
}

void	ms_echo(char **argv)
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
