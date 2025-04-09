/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:12:05 by ekeinan           #+#    #+#             */
/*   Updated: 2025/03/20 09:12:05 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include "libft.h"

# ifndef ARENA_SIZE
#  define ARENA_SIZE 1000//10485760// 10MB
# endif

typedef struct s_arena
{
	void	*pool;
	void	*filled_top;
}			t_arena;

t_arena	arena_create(void);
void	*arena_calloc(t_arena *arena, size_t nmemb, size_t size);
bool	arena_free(t_arena *arena, void *allocated);
bool	arena_destroy(t_arena *arena);

#endif