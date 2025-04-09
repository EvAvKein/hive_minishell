/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:16:49 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:26:47 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move_backwards(char *dest_bytes, char *src_bytes, size_t n)
{
	size_t	i;

	i = n;
	while (i)
	{
		i--;
		dest_bytes[i] = src_bytes[i];
	}
}

static void	move_forwards(char *dest_bytes, char *src_bytes, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest_bytes[i] = src_bytes[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_bytes;
	char	*src_bytes;

	if (!dest && !src)
		return (NULL);
	dest_bytes = (char *) dest;
	src_bytes = (char *) src;
	if (dest < src)
		move_forwards(dest_bytes, src_bytes, n);
	else
		move_backwards(dest_bytes, src_bytes, n);
	return (dest_bytes);
}
