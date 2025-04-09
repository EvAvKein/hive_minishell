/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:54:39 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 17:51:36 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	chr;

	i = 0;
	chr = c;
	while (s[i])
	{
		if (s[i] == chr)
			return (&((char *) s)[i]);
		i++;
	}
	if (chr == '\0')
		return (&((char *) s)[i]);
	return (NULL);
}
