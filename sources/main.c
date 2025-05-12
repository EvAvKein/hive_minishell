/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:27:53 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/12 13:33:37 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
t_shell	*get_shell()
{
	static t_shell shell;
	return (&shell);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;

	(void) argc;
	(void) argv;
	
	// int i = 0;

	shell = get_shell();
	ft_bzero(shell, sizeof(t_shell));
	
	init_signal_handlers();
	
	pid_to_buf(shell->pid);
	shell->envp = envp;
	shell->ms_envp = dup_envp(shell->envp);
	if(!shell->ms_envp)
		fatal_error(shell, "envp duplication failed");
	while (1)
	{
		shell.last_exit_status = 127;
		input = readline(SHELL_PROMPT);
		// if (i++ == 10)
		// 	exit(1);
		if (!input) // replace with EOF (ctrl-D) signal-handler
			continue ;
		if (input_was_entirely_spaces(input))
			continue ;
		add_history(input);
		if (!parsing(shell, input))
		{
			command_cleanup(shell);
			continue ;
		}
		execution(shell);
		command_cleanup(shell);
	}
	shell_cleanup(shell);
	return (EXIT_SUCCESS);
}
