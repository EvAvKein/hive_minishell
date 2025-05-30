/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:02:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/30 10:53:03 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_outfiles(t_shell *shell)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = shell->nodes;
	while (tmp)
	{
		if (tmp->type == OUTFILE || tmp->type == APPENDFILE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	count_redirections(t_shell *shell)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = shell->nodes;
	while (tmp)
	{
		if (tmp->type == INFILE || tmp->type == HEREDOC
			|| tmp->type == OUTFILE || tmp->type == APPENDFILE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	open_infile(t_shell *shell, t_node *node)
{
	if (access(node->argv[0], F_OK) == -1)
	{
		shell->last_exit_status = 2;
		print_err(node->argv[0], " file doesn't exist");
		return ;
	}
	node->fd = open(node->argv[0], O_RDONLY);
	if (node->fd == -1)
		print_err(node->argv[0], " couldn't be opened.");
}

static void	open_outfile_or_appendfile(t_node *node, t_shell *shell)
{
	if (node->type == OUTFILE)
	{
		node->fd = open(node->argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (node->fd == -1)
		{
			shell->last_exit_status = 2;
			print_err(node->argv[0], " couldn't be opened.");
			return ;
		}
	}
	if (node->type == APPENDFILE)
	{
		node->fd = open(node->argv[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (node->fd == -1)
		{
			shell->last_exit_status = 2;
			print_err(node->argv[0], " couldn't be opened.");
		}
	}
}

void	open_redirections(t_shell *shell)
{
	t_node	*node;

	node = shell->nodes;
	while (node)
	{
		if (node->type == INFILE || node->type == HEREDOC)
			open_infile(shell, node);
		if (node->type == OUTFILE || node->type == APPENDFILE)
			open_outfile_or_appendfile(node, shell);
		node = node->next;
	}
}
