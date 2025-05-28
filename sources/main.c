/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:27:53 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/29 14:26:51 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}

void	init_shell(char **envp)
{
	ft_bzero(get_shell(), sizeof(t_shell));
	init_signal_handlers();
	pid_to_buf(get_shell()->pid);
	init_env(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void) argc;
	(void) argv;
	init_shell(envp);
	while (1)
	{
		input = readline(SHELL_PROMPT);
		if (!input)
			break ;
		if (input_was_entirely_spaces(input))
			continue ;
		add_history(input);
		if (!parsing(input))
		{
			command_cleanup();
			continue ;
		}
		if (VERBOSE)
			print_nodes(STDERR_FILENO, get_shell()->nodes);
		execution(get_shell());
		command_cleanup();
	}
	shell_cleanup();
	return (get_shell()->last_exit_status);
}
