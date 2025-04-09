/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:14:02 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/09 15:26:00 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft_plus.h"

typedef enum	e_node_type
{
	INVALID,
	COMMAND,
	HEREDOC,
	INFILE,
	OUTFILE,
	APPENDFILE
}				t_node_type;

typedef struct s_node
{
	t_node_type		type;
	int				argc;
	char			**argv;
	struct s_node	*next;	
}					t_node;

typedef struct	s_shell
{
	char		**env;
	t_node		*nodes;
}				t_shell;

#endif