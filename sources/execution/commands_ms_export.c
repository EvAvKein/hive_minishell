/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ms_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:57:33 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/12 13:11:58 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_envp(t_shell *shell, char **add, int i, int k)
{
	while (shell->ms_envp[i])
	{
		add[i] = ft_strdup(shell->ms_envp[i]);
		if (!add[i])
		{
			free_env_array(add);
			return (1);
		}
		i++;
	}
	while (shell->nodes->argv[k])
	{
		add[i] = ft_strdup(shell->nodes->argv[k]);
		if (!add[i])
		{
			free_env_array(add);
			return (1);
		}
		i++;
		k++;
	}
	add[i] = NULL;
	return (0);
}

static void	print_sorted_envp(char **envp)
{
	int	i;
	int	k;

	i = 0;
	while (envp[i])
	{
		k = 0;
		if (ft_strchr(envp[i], '='))
		{
			write(1, "declare -x ", 11);
			while (envp[i][k] != '=')
			{
				write(1, &envp[i][k], 1);
				k++;
			}
			write(1, "=\"", 2);
			while (envp[i][k++])
				write(1, &envp[i][k], 1);
			write(1, "\"\n", 2);
		}
		i++;
	}
}

static void	sort_envp(char **envp)
{
	int		i;
	char	*tmp;
	bool	swapped;

	i = 0;
	swapped = true;
	while (swapped)
	{
		swapped = false;
		while (envp[i + 1])
		{
			tmp = envp[i];
			if (ft_strncmp(envp[i], envp[i + 1], ft_strlen(envp[i])) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[i + 1];
				envp[i + 1] = tmp;
				swapped = true;
			}
			i++;
		}
		i = 0;
	}
	print_sorted_envp(envp);
}

int	ms_export(t_shell *shell)
{
	char	**add;

	if (shell->nodes->argc > 2 && shell->nodes->argv[1][0] == '-')
		return (1);
	if (shell->nodes->argc > 1)
	{
		add = ft_calloc(shell->nodes->argc
				+ get_env_elements(shell->ms_envp) + 1, sizeof(char *));
		if (!add)
			fatal_error(shell, "export: malloc failed");
		if (append_envp(shell, add, 0, 1) == 1)
			return (1);
		free_env_array(shell->ms_envp);
		shell->ms_envp = add;
		//TODO: the addition is lost from env after the function executes - ie. it doesnt work
	}
	else if (shell->nodes->argc == 1)
	{
		add = dup_envp(shell->ms_envp);
		if (!add)
			fatal_error(shell, "export: malloc failed");
		sort_envp(add);
		free_env_array(add);
	}
	return (0);
}
