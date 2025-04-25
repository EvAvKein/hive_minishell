/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:27:53 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/09 19:43:19by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*input;
	
	(void) argc;
	(void) argv;
	(void) envp;

	ft_bzero(&shell, sizeof(t_shell));

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

	return (EXIT_SUCCESS);
}
