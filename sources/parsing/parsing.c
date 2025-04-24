/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:57:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/24 20:35:31 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Parses the user input stored in `shell`, storing the parsed output inside
 * `shell` on success.
 * 
 * @param shell The address of the initialized shell struct,
 *              from which to get the user input
 *              and in which to store the parsed output.
 * 
 * @returns Whether the parsed input is valid.
 * 
 */
bool	parsing(t_shell *shell, char *input)
{
	t_parsing	parsing;

	parsing = (t_parsing){.i = 0, .input = input, .last_node_preinput = NULL,
		.command_node = NULL, .midparse_nodes = 0};
	if (shell->nodes)
	{
		parsing.last_node_preinput = shell->nodes;
		skip_to_last_node(&parsing.last_node_preinput);
	}
	while (input[parsing.i])
	{
		skip_spaces(&parsing);
		if (!parsing.input[parsing.i])
			break ;
		parsing.command_node = extract_nodes(shell, &parsing);
		if ((!parsing.command_node && !parsing.midparse_nodes)
			|| !sort_nodes_segment(shell, &parsing))
		{
			free(input);
			return (false);
		}
	}
	// print_nodes(STDERR_FILENO, shell->nodes);
	free(input);
	return (true);
}
