/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:33:50 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:30:15 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_is_matching(
		const char *str, const char *to_find, size_t outer_i, size_t limit_i
)
{
	size_t	i;

	i = 0;
	while (outer_i + i < limit_i && to_find[i])
	{
		if (str[i] != to_find[i])
			return (0);
		i++;
	}
	if (outer_i + i == limit_i && to_find[i])
		return (0);
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!little[0])
		return ((char *) big);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0] && str_is_matching(&big[i], little, i, len))
			return (&((char *) big)[i]);
		i++;
	}
	return (NULL);
}
