/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:57:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/19 15:46:11 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	reset_parsing_for_next_segment(t_parsing *parsing)
{
	skip_spaces(parsing);
	parsing->node_before_command = get_shell()->nodes;
	skip_to_last_node(&parsing->node_before_command);
	parsing->midparse_nodes = 0;
	parsing->command_node = NULL;
}

/**
 * 
 * Parses user input and stores the parsed output inside `shell` on success.
 * 
 * @param input The user input.
 * 
 * @returns Whether the parsed input is valid.
 * 
 */
bool	parsing(char *input)
{
	t_parsing	parsing;

	parsing = (t_parsing){.i = 0, .input = input, .node_before_command = NULL,
		.command_node = NULL, .midparse_nodes = 0, .piping = false};
	delete_void_expansions(input);
	while (input[parsing.i])
	{
		reset_parsing_for_next_segment(&parsing);
		if (!parsing.input[parsing.i]
			|| (parsing.piping && input[parsing.i] == '|'))
			break ;
		if (!extract_nodes(&parsing) || !sort_nodes_segment(&parsing))
		{
			free(input);
			return (false);
		}
	}
	free(input);
	if (parsing.piping && print_err("syntax error: ambiguous pipe", ""))
	{
		get_shell()->last_exit_status = EXIT_INCORRECT;
		return (false);
	}
	return (true);
}
