/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:22:49 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:26:24 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_bytes;
	unsigned char	*s2_bytes;

	if (!n)
		return (0);
	i = 0;
	s1_bytes = (unsigned char *) s1;
	s2_bytes = (unsigned char *) s2;
	while (i < n)
	{
		if (s1_bytes[i] - s2_bytes[i])
			return (s1_bytes[i] - s2_bytes[i]);
		i++;
	}
	if (i < n && s2_bytes[i])
		return (s1_bytes[i] - s2_bytes[i]);
	return (0);
}
