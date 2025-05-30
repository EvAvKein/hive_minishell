/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:13:53 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/30 10:51:10 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef enum exec_macros
{
	READ = 0,
	WRITE,
	MAX_CMDS = 256,
}	t_exec_macros;

typedef struct s_exec
{
	pid_t	pids[MAX_CMDS];
	int		pid_count;
}			t_exec;

typedef struct s_fd
{
	int	pipe_fd[2];
	int	prev_fd;
	int	out;
}			t_fd;

#endif