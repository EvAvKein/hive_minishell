/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:20:37 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/25 09:34:28 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
void	print_node_type(int fd, t_node_type type)
{
	if (type == UNPARSED)
		ft_dprintf(fd, "UNPARSED");
	else if (type == COMMAND)
		ft_dprintf(fd, "COMMAND");
	else if (type == HEREDOC)
		ft_dprintf(fd, "HEREDOC");
	else if (type == HEREDOC_QUOTED)
		ft_dprintf(fd, "HEREDOC_QUOTED");
	else if (type == INFILE)
		ft_dprintf(fd, "INFILE");
	else if (type == OUTFILE)
		ft_dprintf(fd, "OUTFILE");
	else if (type == APPENDFILE)
		ft_dprintf(fd, "APPENDFILE");
	else
		ft_dprintf(fd, "[TYPE NOT FOUND (%d)]", type);
}

/**
 * 
 * TODO: Write these docs 
 * 
 */
void	print_nodes(int fd, t_node *node)
{
	int		i;
	bool	print_finale;

	print_finale = !!node;
	while (node)
	{
		ft_dprintf(fd, "│\n├─┬─ type: ");
		print_node_type(fd, node->type);
		ft_dprintf(fd, "\n│ └─┬─ argc: %d\n", node->argc);
		i = -1;
		while (node->argv[++i])
		{
			if (node->argv[i + 1])
				ft_dprintf(fd, "│   ├─── argv[%d]: \"%s\"\n", i, node->argv[i]);
			else
				ft_dprintf(fd, "│   └─── argv[%d]: \"%s\"\n", i, node->argv[i]);
		}
		node = node->next;
	}
	if (print_finale)
		ft_dprintf(fd, "│\n");
}
