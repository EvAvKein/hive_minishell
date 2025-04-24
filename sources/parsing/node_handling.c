/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:31:49 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/24 16:09:28 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	str_to_nodes(t_shell *shell, t_parsing *parsing, t_node *cmd_node)
{
	int		cmd_i;
	char	*input;

	cmd_i = 0;
	input = parsing->input;
	while (input[parsing->i])
	{
		skip_spaces(parsing);
		if (input[parsing->i] == '|')
			return (true);
		if (!handle_operator(shell, parsing))
			return (false); /** Does this need extra handling? */
		skip_spaces(parsing);
		if (input[parsing->i] == '|')
			return (true);
		if (cmd_node && input[parsing->i] && !operator_of_c(&input[parsing->i]))
		{
			cmd_node->argv[cmd_i] = extract_arg(parsing);
			if (!cmd_node->argv[cmd_i++])
				return (false);
		}
	}
	return (true);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
t_node	*append_new_node(t_shell *shell, int argc)
{
	t_node	*new_node;
	t_node	*node_for_append;
	
	new_node = ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL); /** TODO: Print ENOMEM */
	new_node->argc = argc;
	new_node->argv = ft_calloc(argc + 1, sizeof(char *));
	if (!new_node->argv)
	{
		free(new_node);
		return (NULL); /** TODO: Print ENOMEM */
	}
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
 * TODO: Write these docs
 * 
 */
t_node	*extract_nodes(t_shell *shell, t_parsing *parsing)
{
	t_node	*cmd_node;
	int		argc;

	cmd_node = NULL;
	argc = str_to_argc(&parsing->input[parsing->i],
		(t_str_to_argc_vars){.i = 0, .argc = 0, .in_arg = false,
		.in_quote = '\0', .in_operator = {'\0', '\0', '\0'}});
	if (argc < 0)
		return (NULL);
	if (argc)
	{
		cmd_node = append_new_node(shell, argc);
		if (!cmd_node)
			return (NULL);
		cmd_node->type = COMMAND;
	}
	str_to_nodes(shell, parsing, cmd_node);
	return (cmd_node);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	sort_nodes_segment(t_shell *shell, t_parsing *parsing)
{
	t_node_sort sort;

	if (!parsing->midparse_nodes)
		return (true);
	sort = (t_node_sort){.node = shell->nodes, .command_node = parsing->command_node,
		.infile_count = 0, .infile_arr = NULL,
		.outfile_count = 0, .outfile_arr = NULL};
	skip_to_last_node(&sort.node);
	count_segment_nodes(parsing, &sort);
	if (!collect_segment_nodes(&sort))
		return (false);
	sort.attach = (t_node_sort_reattach){.prev_node = parsing->last_node_preinput,
		.infiles = link_collected_nodes(&sort.infile_arr, 0), .start = NULL,
		.outfiles = link_collected_nodes(&sort.outfile_arr, 0)};
	reattach_nodes(parsing, &sort.attach);
	if (!parsing->last_node_preinput)
		shell->nodes = sort.attach.start;
	return (true);
}
