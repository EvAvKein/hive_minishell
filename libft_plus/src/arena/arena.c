/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:11:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/03/20 09:36:02 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_arena	arena_create(void)
{
	t_arena	arena;

	arena.pool = malloc(ARENA_SIZE);
	arena.filled_top = arena.pool;
	return (arena);
}

size_t	arena_available_top(t_arena *arena)
{
	return (ARENA_SIZE - (arena->filled_top - arena->pool) - sizeof(size_t));
}

static void	*arena_malloc(t_arena *arena, size_t bytes)
{
	void	*allocated;

	if (bytes > arena_available_top(arena))
		return (NULL);
	*(size_t *)arena->filled_top = bytes;
	allocated = arena->filled_top + sizeof(size_t);
	arena->filled_top = allocated + bytes;
	return (allocated);
}

void	*arena_calloc(t_arena *arena, size_t nmemb, size_t size)
{
	void	*allocated;
	size_t	bytes;

	if (!size || !nmemb)
		return (NULL);
	bytes = nmemb * size;
	if (bytes / nmemb != size)
		return (NULL);
	allocated = arena_malloc(arena, bytes);
	if (!allocated)
		return (NULL);
	ft_bzero(allocated, bytes);
	return (allocated);
}


bool	arena_destroy(t_arena *arena)
{
	free(arena->pool);
	arena->pool = NULL;
	arena->filled_top = NULL;
	return (true);
}
