/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:08:44 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:26:35 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*src_bytes;
	char	*dest_bytes;

	if (!dest && !src)
		return (NULL);
	i = 0;
	src_bytes = (char *) src;
	dest_bytes = (char *) dest;
	while (i < n)
	{
		dest_bytes[i] = src_bytes[i];
		i++;
	}
	return (dest);
}
