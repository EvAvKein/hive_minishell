/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:57:43 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:29:06 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	dest_i;
	size_t	src_i;
	size_t	length;

	length = ft_strlen(src);
	if (!size)
		return (length);
	dest_i = 0;
	src_i = 0;
	while (dest_i < size - 1 && src[src_i])
		dest[dest_i++] = ((char *) src)[src_i++];
	dest[dest_i] = '\0';
	return (length);
}
