/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:52:18 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 18:20:51 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*clear_both(t_list *map, void *content, void (*del)(void *))
{
	del(content);
	ft_lstclear(&map, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*map_current;
	void	*modified_content;

	if (!lst || !f || !del)
		return (NULL);
	modified_content = f(lst->content);
	map = ft_lstnew(modified_content);
	if (!map)
	{
		del(modified_content);
		return (NULL);
	}
	map_current = map;
	while (1)
	{
		if (!lst->next)
			return (map);
		modified_content = f(lst->next->content);
		map_current->next = ft_lstnew(modified_content);
		if (!map_current->next)
			return (clear_both(map, modified_content, del));
		lst = lst->next;
		map_current = map_current->next;
	}
}
