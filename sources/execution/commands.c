/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/16 14:27:51 by ahavu            ###   ########.fr       */
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
int	check_removables(char *line, char **remove)
{
	int	i;

	i = 0;
	while (remove[i])
	{
		if (!ft_strncmp(line, remove[i], ft_strlen(remove[i])))
			return (1);
		i++;
	}
	return (0);
}

char **set_removables(t_shell *shell)
{
	char **ret;
	int	i;
	int	k;

	i = 0;
	k = 1;
	ret = ft_calloc(shell->nodes->argc, sizeof(char *));
	if (!ret)
		//error, return NULL
	while (shell->nodes->argv[k])
	{
		ret[i] = shell->nodes->argv[k];
		i++;
		k++;
	}
	return (ret);
}

void	ms_unset(t_shell *shell)
{
	int		i;
	int		k;
	char	**dup;
	char	**remove;

	dup = ft_calloc(get_env_elements, sizeof(char *));
	if (!dup)
		//error
	remove = set_removables(shell);
	if (!remove)
		//error
	i = 0;
	k = 0;
	while (shell->env[i])
	{
		if (!check_removables(shell->env[i], remove))
		{
			dup[k] = shell->env[i];
			i++;
		}
		else
			i++;
	}
}
