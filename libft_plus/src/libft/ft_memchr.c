/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:12:55 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:26:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_bytes;
	unsigned char	c_byte;

	i = 0;
	s_bytes = (unsigned char *) s;
	c_byte = (unsigned char) c;
	while (i < n)
	{
		if (s_bytes[i] == c_byte)
			return (&s_bytes[i]);
		i++;
	}
	return (NULL);
}
