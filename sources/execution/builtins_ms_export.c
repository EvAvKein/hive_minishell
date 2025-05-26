/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ms_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:57:33 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/26 13:54:21 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exportables_names(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!is_valid_envname(argv[i]))
		{
			print_err(argv[i], ": not a valid var name");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ms_export(t_shell *shell)
{
	size_t	i;

	if (check_exportables_names(shell->nodes->argv) == 1)
	{
		return (1);
	}
	if (shell->nodes->argc > 1)
	{
		i = 1;
		while (shell->nodes->argv[i])
		{
			if (env_add(shell->nodes->argv[i]) == false)
				return (1);
			shell->nodes->argv[i] = NULL;
			i++;
		}
	}
	else if (shell->nodes->argc == 1)
		export_just_print(shell);
	return (0);
}
