/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:31:49 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/19 09:36:45 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Allocates for a new node with an argument vector
 * according to the provided `argc`,
 * appending the node at the end of `shell`'s linked list of nodes.
 * 
 * @param argc The argument count of this node,
 *             according to which to allocate an argument vector for the node.
 * 
 * @returns A pointer to the new node (or `NULL` on memory allocation failure).
 * 
 */
t_node	*append_new_node(t_shell *shell, int argc)
{
	t_node	*new_node;
	t_node	*node_for_append;
	
	new_node = ft_calloc(1, sizeof(t_node));
	if (!new_node && print_err("parsing: ", strerror(ENOMEM)))
		return (NULL);
	new_node->argc = argc;
	new_node->argv = ft_calloc(argc + 1, sizeof(char *));
	if (!new_node->argv)
	{
		print_err("parsing: ", strerror(ENOMEM));
		free(new_node);
		return (NULL);
	}
	new_node->fd = -1;
	if (!shell->nodes)
	{
		shell->nodes = new_node;
		return (new_node);
	}
	node_for_append = shell->nodes;
	skip_to_last_node(&node_for_append);
	node_for_append->next = new_node;
	new_node->prev = node_for_append;
	return (new_node);
}

/**
 * 
 * Parses the next 'simple command', adding command arguments (if any)
 * to the provided command node and appending any redirection nodes at the end.
 * 
 * @param cmd_node The command node in which to add command arguments.
 * Assumes enough space is already allocated in its vector to fit all arguments.
 * 
 * @returns Whether all node creations were successful.
 * 
 */
static bool	str_to_nodes(t_shell *shell, t_parsing *parsing, t_node *cmd_node)
{
	int		cmd_i;
	char	*input;

	cmd_i = 0;
	input = parsing->input;
	while (input[parsing->i])
	{
		skip_spaces(parsing);
		if (skip_pipe(parsing))
			return (true);
		if (!handle_redirect(shell, parsing))
			return (false);
		skip_spaces(parsing);
		if (skip_pipe(parsing))
			return (true);
		if (cmd_node && input[parsing->i] && !redirect_of_c(&input[parsing->i]))
		{
			cmd_node->argv[cmd_i] = extract_arg(shell, parsing, false);
			if (!cmd_node->argv[cmd_i++])
				return (false);
		}
	}
	return (true);
}

/**
 * 
 * Parses the next 'simple command' - adding any command to the end
 * of the `shell`'s linked list of nodes, followed by that command's
 * redirection nodes (if any).
 * 
 * @returns Whether a 'valid simple' was found
 *          and memory allocations were successful.
 * 
 */
bool	extract_nodes(t_shell *shell, t_parsing *parsing)
{
	int		argc;

	argc = str_to_argc(&parsing->input[parsing->i],
		(t_str_to_argc_vars){.i = 0, .argc = 0, .in_arg = false,
		.in_quote = '\0', .redirect = {'\0', '\0', '\0'}});
	if (argc < 0)
	{
		get_shell()->last_exit_status = 2;
		return (false);
	}
	if (argc)
	{
		parsing->command_node = append_new_node(shell, argc);
		if (!parsing->command_node)
			return (false);
		parsing->command_node->type = COMMAND;
	}
	parsing->piping = false;
	if (!str_to_nodes(shell, parsing, parsing->command_node))
		return (false);
	return (true);
}

/**
 * 
 * Sorts the newly-added nodes according to data accumulated in the provided
 * `parsing` struct:
 * Moving any infiles and heredocs nodes to the beginning of the segement,
 * any command node to the middle of the segement,
 * and any outfile and appendfile nodes to the end of the segement.
 * 
 * @returns Whether the sorting process (with its necessary memory allocations)
 *          was successful.
 * 
 */
bool	sort_nodes_segment(t_shell *shell, t_parsing *parsing)
{
	t_node_sort sort;

	if (!parsing->midparse_nodes)
		return (true);
	sort = (t_node_sort){.node = shell->nodes,
		.command_node = parsing->command_node,
		.infile_count = 0, .infile_arr = NULL,
		.outfile_count = 0, .outfile_arr = NULL};
	skip_to_last_node(&sort.node);
	count_segment_nodes(parsing, &sort);
	if (!collect_segment_nodes(&sort))
		return (false);
	sort.attach = (t_node_sort_reattach){
		.prev_node = parsing->node_before_command,
		.infiles = link_collected_nodes(&sort.infile_arr, 0), .start = NULL,
		.outfiles = link_collected_nodes(&sort.outfile_arr, 0)};
	reattach_nodes(parsing, &sort.attach);
	if (!parsing->node_before_command)
		shell->nodes = sort.attach.start;
	return (true);
}
