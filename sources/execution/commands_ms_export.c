/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ms_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:57:33 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/14 11:35:22 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_export(t_shell *shell)
{
	int		i;
	int		k;
	char	**add;

	i = 0;
	k = 0;
	add = ft_calloc(shell->nodes->argc + get_env_elements(shell->env),
			sizeof(char *));
	if (!add)
		//error TODO
	while(shell->env[k])
	{
		add[i] = shell->env[k];
		i++;
		k++;
	}
	k = 0;
	while(shell->nodes->argv[k])
	{
		add[i] = shell->nodes->argv[k];
		i++;
		k++;
	}
	shell->env = add;
}
