/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:27:53 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/21 18:00:05 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void) argc;
	(void) argv;
	ft_bzero(get_shell(), sizeof(t_shell));
	init_signal_handlers();
	pid_to_buf(get_shell()->pid);
	init_env(envp);
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
		print_nodes(STDERR_FILENO, get_shell()->nodes);
		// execution(shell);
		command_cleanup();
	}
	shell_cleanup();
	return (get_shell()->last_exit_status);
}
