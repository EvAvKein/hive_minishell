/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:06:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/29 09:50:28 by ekeinan          ###   ########.fr       */
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
 *          (or `NULL` on memory allocation failure).
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
void	*free_str_arr(char **arr)
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

/**
 * 
 * TODO: Write these docs
 * 
 * @param arr A null-terminated array of strings.
 * 
 */
// char	*str_arr_join(char **arr)
// {
// 	char	*str;
// 	size_t	str_i;
// 	size_t	arr_i;
// 	size_t	len;

// 	if (!arr)
// 		return (NULL);
// 	arr_i = 0;
// 	len = 0;
// 	while (arr[arr_i])
// 		len += ft_strlen(arr[arr_i++]);
// 	str = ft_calloc(len + 1, sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	arr_i = 0;
// 	str_i = 0;
// 	while (arr[arr_i])
// 	{
// 		ft_strlcpy(&str[str_i], arr[arr_i], ft_strlen(arr_i) + 1);
// 		arr_i++;
// 		while (str[str_i])
// 			str_i++;
// 	}
// 	return (str);
// }
