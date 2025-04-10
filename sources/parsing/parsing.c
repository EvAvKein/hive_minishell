/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:39:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/09 19:42:09 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_shell *shell)
{
	shell->nodes = input_to_nodes(shell->latest_input);
	if (!shell->nodes)
		shell_exit(shell, 1);
	// ^ NOTE: Exit here might not even be necessary.
	//         Might be better to always exit inside with specific status
}
