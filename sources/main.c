/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:27:53 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/12 13:26:02 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;
	
	(void) argc;
	(void) argv;

	int i = 0;

	ft_bzero(&shell, sizeof(t_shell));
	shell.envp = envp;
	shell.ms_envp = dup_envp(shell.envp);
	if(!shell.ms_envp)
		fatal_error(&shell, "envp duplication failed");
	while (1)
	{
		i++;
		input = readline(SHELL_PROMPT);
		//printf("%s\n", input);
		if (i == 10)
			exit(1);
		if (!input) // replace with EOF (ctrl-D) signal-handler
			continue;
		if (input_was_entirely_spaces(input))
			continue;
		add_history(input);
		if (!parsing(&shell, input))
		{
			command_cleanup(&shell);
			continue ;
		}
		// execution(&shell);
		command_cleanup(&shell);
	}
	free_env_array(shell.ms_envp);
	return (EXIT_SUCCESS);
}
