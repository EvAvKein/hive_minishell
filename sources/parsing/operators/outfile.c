/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:31:03 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 15:49:36 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_outfile(t_shell *shell, t_node *preceding_node, size_t *i)
{
	(void) shell;
	(void) preceding_node;
	(void) i;
	
	printf("Outfile detected: '%c' @ i-%lu\n", shell->latest_input[*i], *i);

	(*i)++;
	
	return (true);
}
