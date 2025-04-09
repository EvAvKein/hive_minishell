/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:06:58 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:28:48 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	joined_len;
	char	*joined;
	size_t	joined_i;
	size_t	s_i;

	if (!s1 || !s2)
		return (NULL);
	joined_len = ft_strlen(s1) + ft_strlen(s2);
	joined = ft_calloc(joined_len + 1, sizeof(char));
	if (joined == NULL)
		return (NULL);
	joined_i = 0;
	s_i = 0;
	while (s1[s_i])
		joined[joined_i++] = s1[s_i++];
	s_i = 0;
	while (s2[s_i])
		joined[joined_i++] = s2[s_i++];
	joined[joined_i] = 0;
	return (joined);
}
