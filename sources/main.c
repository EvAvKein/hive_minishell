/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:27:53 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/24 08:54:38 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*input;
	
	(void) argc;
	(void) argv;

	ft_bzero(&shell, sizeof(t_shell));
	shell.envp = envp;
	shell.ms_envp = dup_envp(shell.envp);
	if(!shell.ms_envp)
	{
		perror("envp duplication failed :( goodbye\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		input = readline("shellGBTQ+ >");
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
		execution(&shell);
		command_cleanup(&shell);
	}
	free_env_array(shell.ms_envp);
	return (EXIT_SUCCESS);
}
