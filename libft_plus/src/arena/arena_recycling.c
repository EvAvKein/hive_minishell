/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_recycling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:14:36 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/09 09:18:35 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

bool	arena_free(t_arena *arena, void *allocated)
{
	void	*alloc_start;
	size_t	size;

	if (!allocated)
		return (false);
	alloc_start = allocated - sizeof(size_t);
	size = *((size_t *)alloc_start) + sizeof(size_t);
	ft_bzero(alloc_start, size);
	return (true);
}

static void	*arena_malloc_gap(t_arena *arena, void *search_start, size_t bytes)
{
	void	*allocated;
	size_t	i;
	
	if (search_start)
	{
		if (search_start < arena->pool
			|| search_start > arena->pool + ARENA_SIZE)

		i = search_start - arena->pool;
	}
	else
		i = 0;
	*(size_t *)arena->filled_top = bytes;
	allocated = arena->filled_top + sizeof(size_t);
	arena->filled_top = allocated + bytes;
	return (allocated);
}

void	*arena_calloc_gap(
	t_arena *arena, void *search_start, size_t nmemb, size_t size)
{
	size_t	bytes;

	if (!size || !nmemb)
		return (NULL);
	bytes = nmemb * size;
	if (bytes / nmemb != size)
		return (NULL);
	return (arena_malloc_gap(arena, search_start, bytes));
}

// void	*arena_realloc()
// {
	
// }
