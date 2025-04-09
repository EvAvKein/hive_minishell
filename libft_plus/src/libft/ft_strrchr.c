/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:39:35 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 17:51:19 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	chr;
	char			*addr;

	i = 0;
	chr = c;
	addr = NULL;
	while (s[i])
	{
		if (s[i] == chr)
			addr = &((char *) s)[i];
		i++;
	}
	if (chr == '\0')
		return (&((char *) s)[i]);
	return (addr);
}
