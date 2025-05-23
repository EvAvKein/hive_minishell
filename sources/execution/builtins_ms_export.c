/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ms_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:57:33 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/23 15:20:06 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_envp(t_shell *shell, char **add, int i, int k)
{
	while (shell->ms_envp[i])
	{
		add[i] = shell->ms_envp[i];
		if (!add[i])
		{
			free_env_array(add);
			return (1);
		}
		i++;
	}
	while (shell->nodes->argv[k])
	{
		add[i] = shell->nodes->argv[k];
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

static int	check_exportables_names(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!isalpha(argv[i][0]) && argv[i][0] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ms_export(t_shell *shell)
{
	char	**add;

	if (check_exportables_names(shell->nodes->argv) == 1)
	{
		print_err(shell->nodes->argv[1], ": not a valid var name");
		return (1);
	}
	if (shell->nodes->argc > 1)
	{
		add = ft_calloc(shell->nodes->argc
				+ get_env_elements(shell->ms_envp) + 1, sizeof(char *));
		if (!add)
			fatal_error(shell, "export: malloc failed");
		if (append_envp(shell, add, 0, 1) == 1)
			return (1);
		shell->ms_envp = add;
		free(add);
	}
	else if (shell->nodes->argc == 1)
	{
		export_just_print(shell);
		shell_cleanup(shell);
	}
	return (0);
}
