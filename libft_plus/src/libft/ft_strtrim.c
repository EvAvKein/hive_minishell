/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:57 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:30:33 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char chr, char const *set)
{
	size_t	i;

	i = 0;
	if (!set[i])
		return (0);
	while (set[i])
		if (set[i++] == chr)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	length;
	size_t	start_i;
	size_t	end_i;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	length = ft_strlen(s1);
	if (!length)
		return (ft_calloc(1, sizeof(char)));
	start_i = 0;
	end_i = length - 1;
	while (char_in_set(s1[start_i], set) && start_i < length)
		start_i++;
	while (char_in_set(s1[end_i], set) && end_i > 0)
		end_i--;
	if (end_i < start_i)
		return (ft_strdup(""));
	length = end_i - start_i;
	trimmed = ft_calloc(length + 2, sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, &s1[start_i], length + 2);
	return (trimmed);
}
