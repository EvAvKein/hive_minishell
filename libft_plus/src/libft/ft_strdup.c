/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:53:53 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:28:32 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	length;
	char	*string;

	length = ft_strlen(src);
	string = ft_calloc(length + 1, sizeof(char));
	if (!string)
		return (NULL);
	ft_strlcpy(string, src, length + 1);
	return (string);
}
