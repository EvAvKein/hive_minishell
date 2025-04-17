/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appendfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:30:26 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 16:21:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_appendfile(t_shell *shell, t_node *preceding_node, size_t *i)
{
	(void) shell;
	(void) preceding_node;
	(void) i;

	printf("Appendfile detected: \"%.2s\" @ i-%lu\n", &shell->latest_input[*i], *i);
	
	(*i) += 2;
	
	return (true);
}
