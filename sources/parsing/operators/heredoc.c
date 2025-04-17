/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:29:59 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 16:21:18 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_heredoc(t_shell *shell, t_node *preceding_node, size_t *i)
{
	(void) shell;
	(void) preceding_node;
	(void) i;
	
	printf("Heredoc detected: \"%.2s\" @ i-%lu\n", &shell->latest_input[*i], *i);

	(*i) += 2;

	return (true);
}
