/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ms_export_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:58:43 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/20 13:02:59 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_envp(char **envp)
{
	int	i;
	int	k;

	i = 0;
	while (envp[i])
	{
		k = 0;
		printf("declare -x ");
		if (!ft_strchr(envp[i], '='))
		{
			printf("%s\n", envp[i]);
			break ;
		}
		while (envp[i][k] != '=')
		{
			printf("%c", envp[i][k]);
			k++;
		}
		printf("=\"");
		while (envp[i][++k])
			printf("%c", envp[i][k]);
		printf("\"\n");
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
}

void	export_just_print(t_shell *shell)
{
	char **add;
	
	add = dup_envp(shell->ms_envp);
	if (!add)
		fatal_error(shell, "export: malloc failed");
	sort_envp(add);
	print_sorted_envp(add);
	free_env_array(add);
}
