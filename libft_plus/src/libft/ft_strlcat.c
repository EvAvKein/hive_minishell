/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:36:46 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:28:58 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		dest_i;
	size_t		src_i;
	size_t		dest_len;
	size_t		src_len;
	size_t		return_val;

	if (!size && (!dest || !src))
		return (0);
	dest_i = 0;
	src_i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen((char *) src);
	if (!size)
		return (src_len);
	if (size > dest_len)
		return_val = src_len + dest_len;
	else
		return_val = src_len + size;
	while (dest[dest_i] && dest_i < size - 1)
		dest_i++;
	while (src[src_i] && dest_i < size - 1)
		dest[dest_i++] = src[src_i++];
	if (dest_i >= dest_len)
		dest[dest_i] = '\0';
	return (return_val);
}
