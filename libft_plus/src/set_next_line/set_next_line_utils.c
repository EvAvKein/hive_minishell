/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:21:17 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/18 10:56:47 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_next_line.h"

bool	set_str_and_return(char **str_ptr, char *str, bool return_bool)
{
	if (str && !*str)
	{
		free(str);
		str = NULL;
	}
	*str_ptr = str;
	return (return_bool);
}

size_t	ft_strlen_until_nl(char *s, ssize_t *nl_i)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
	{
		*nl_i = i;
		i++;
	}
	return (i);
}

char	*ft_strdup_until_nl(char *src, ssize_t *nl_i)
{
	char	*dup;
	size_t	i;

	dup = malloc((ft_strlen_until_nl(src, nl_i) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dup[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
