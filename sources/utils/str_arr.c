/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:06:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/25 19:03:47 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @returns The amount of strings stored in provided `str_arr`.
 * 
 */
size_t	str_arr_count(char **str_arr)
{
	size_t	i;

	if (!str_arr)
		return (0);
	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

/**
 * 
 * @returns A newly heap-allocated array,
 *          storing the same strings/addresses as in the provided `str_arr`
 *          (or `NULL` if allocation fails).
 * 
 */
char	**str_arr_shallow_copy(char **str_arr)
{
	char	**copy;
	size_t	i;

	if (!str_arr)
		return (NULL);
	copy = ft_calloc(str_arr_count(str_arr) + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (str_arr[i])
	{
		copy[i] = str_arr[i];
		i++;
	}
	return (copy);
}

/**
 * 
 * Frees all strings inside the provided array of strings,
 * freeing the provided array itself at the end.
 * 
 * @returns `NULL` (for external line-saving reason, due to Norminette).
 * 
 */
void	*free_str_array(char **arr)
{
	size_t	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}
