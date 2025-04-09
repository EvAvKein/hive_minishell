/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:43:13 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:30:41 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;
	size_t	substr_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= ft_strlen(s))
	{
		start = ft_strlen(s);
		substr_len = 0;
	}
	else if (len > s_len - start)
		substr_len = s_len - start;
	else
		substr_len = len;
	str = ft_calloc(substr_len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s[start], substr_len + 1);
	return (str);
}
