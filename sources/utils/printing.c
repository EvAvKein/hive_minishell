/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:20:37 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/27 09:13:19 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Prints SHELL_NAME, a colon and space, the two provided strings,
 * and a newline, to STDERR.
 * 
 * @returns The return value of `ft_dprintf`
 *          (amount of characters written, or -1 on write error).
 * 
 */
size_t	print_err(char *part1, char *part2)
{
	return (ft_dprintf(STDERR_FILENO, SHELL_NAME ": %s%s\n", part1, part2));
}

/**
 * 
 * Prints `part1` and `part2` followed by a newline to STDERR,
 * but only if the VERBOSE setting is truthy.
 * 
 * @param part1 A string (not null-checked).
 * 
 * @param part2 A string (not null-checked).
 * 
 * @returns If VERBOSE is on, the return value of `ft_dprintf`
 *          (amount of characters written, or -1 on write error).
 *          If VERBOSE is off, '-1'.
 * 
 */
int	verbose(char *part1, char *part2)
{
	if (VERBOSE)
		return (ft_dprintf(STDERR_FILENO, "%s%s\n", part1, part2));
	return (-1);
}

/**
 * 
 * Prints the name of the provided node type
 * (which would otherwise be printed as its enum value).
 *  
 * @param fd   The file descriptor to which to write the node type.
 * 
 * @param node The node type for which to print the name.
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
 * Prints a tree-like visualization for the provided linked list of nodes,
 * displaying the node's type, argument count, and argument values.
 * 
 * @param fd   The file descriptor to which to write the visualization.
 * 
 * @param node The start of the linked list of nodes to be visualized.
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

/**
 * 
 * Writes the current process' ID
 * (or an error indicator on failure)
 * to the provided buffer, for later printing.
 * 
 * @param buf A buffer for writing the PID or the error indicator,
 *            assumed to have a size of (at least) 20.
 * 
 * @returns The buffer.
 * 
 */
char	*pid_to_buf(char buf[20])
{
	int		fd;
	int		i;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0 || read(fd, buf, 20) < 0)
		ft_strlcpy(buf, "[PID UNAVAILABLE]", 18);
	else
	{
		i = 0;
		while (buf[i] && buf[i] != ' ')
			i++;
		buf[i] = '\0';
	}
	if (fd >= 0)
		close(fd);
	return (buf);
}
