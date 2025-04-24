/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:31:26 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/23 10:40:08 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	parse_plusequals(t_shell *shell,t_parsing *parsing)
{
	(void) shell;
	(void) parsing;

	printf("Appendfile detected: \"%.2s\" @ i-%lu\n",
		&parsing->input[parsing->i], parsing->i);
	
	parsing->i += 2;
	
	return (true);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	parse_equals(t_shell *shell,t_parsing *parsing)
{
	(void) shell;
	(void) parsing;

	printf("Appendfile detected: \"%.2s\" @ i-%lu\n",
		&parsing->input[parsing->i], parsing->i);
	
	parsing->i += 2;
	
	return (true);
}
