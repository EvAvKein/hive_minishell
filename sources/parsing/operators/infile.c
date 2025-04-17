/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:30:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 15:51:37 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_infile(t_shell *shell, t_node *preceding_node, size_t *i)
{
	(void) shell;
	(void) preceding_node;
	(void) i;
	
	printf("Infile detected: '%.2s' @ i-%lu\n", &shell->latest_input[*i], *i);
	
	(*i)++;
	
	return (true);
}
