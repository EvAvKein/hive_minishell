/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:21:54 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/10 08:26:19 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file We don't need a file just for space-related functions.
 *       Combine into larger utils file when we have other utils.
 */

#include "minishell.h"

bool is_space(char c)
{
	return (c == ' ' || (c <= '\r' && c >= '\t'));
}

bool is_entirely_spaces(char *string)
{
	if (!string)
		return (false);
	while (is_space(*string))
		string++;
	return (*string == '\0');
}
