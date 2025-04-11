/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/11 15:53:28 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while(envp[i])
		{
			if (ft_strchr(envp[i], '='))
				printf("%s\n", envp[i]);
			i++;
		}
	}
}

void	ms_pwd(void)
{
	char	*path;
	
	path = getcwd(NULL, 0);
	if (!path)
		//error
	printf("%s\n", path);
	free(path);
}

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
