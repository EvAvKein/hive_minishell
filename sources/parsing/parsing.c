/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:57:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/12 13:21:48 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void reset_parsing_for_next_segment(
	t_shell *shell, t_parsing *parsing)
{
	parsing->node_before_command = shell->nodes;
	skip_to_last_node(&parsing->node_before_command);
	parsing->midparse_nodes = 0;
	parsing->command_node = NULL;
}

/**
 * 
 * Parses user input and stores the parsed output inside `shell` on success.
 * 
 * @param shell The address of the initialized shell struct
 *              in which to store the parsed output.
 * 
 * @param input The user input.
 * 
 * @returns Whether the parsed input is valid.
 * 
 */
bool	parsing(t_shell *shell, char *input)
{
	t_parsing	parsing;

	parsing = (t_parsing){.i = 0, .input = input, .node_before_command = NULL,
		.command_node = NULL, .midparse_nodes = 0, .piping = false};
	while (input[parsing.i])
	{
		reset_parsing_for_next_segment(shell, &parsing);
		skip_spaces(&parsing);
		if (parsing.piping && input[parsing.i] == '|')
			break ;
		if (!parsing.input[parsing.i])
			break ;
		if (!extract_nodes(shell, &parsing)
			|| !sort_nodes_segment(shell, &parsing))
		{
			free(input);
			return (false);
		}
	}
	//print_nodes(STDERR_FILENO, shell->nodes);
	free(input);
	if (parsing.piping)
	{
		ft_dprintf(2, "ambiguous pipe (PLACEHOLDER ERROR)\n");
		return (false);
	}
	//print_nodes(STDERR_FILENO, shell->nodes);
	return (true);
}
