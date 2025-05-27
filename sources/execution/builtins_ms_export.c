/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ms_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:57:33 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/27 17:08:29 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_export(t_shell *shell)
{
	t_node	*node;
	size_t	i;

	node = shell->nodes;
	while (node && node->type != COMMAND)
		node = node->next;
	if (node->argc > 1)
	{
		i = 1;
		while (node->argv[i])
		{
			if (!is_valid_envname(node->argv[i]))
			{
				print_err(node->argv[i++], ": not a valid identifier");
				continue ;
			}
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
