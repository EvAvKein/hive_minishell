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
	size_t	input_i;
	
	(void) argc;
	(void) argv;
	(void) envp;

	ft_bzero(&shell, sizeof(t_shell));

	while (1)
	{
		input_i = 0;
		input = readline("shellGBTQ+ >");
		if (!input) // replace with EOF (ctrl-D) signal-handler
			continue;
		if (is_entirely_spaces(input))
		{
			free(input);
			continue;
		}
		add_history(input);
		shell.latest_input = input;
		if (!parsing(&shell))
		{
			free(shell.latest_input);
			continue ;
		}
		execution(&shell);
		free(shell.latest_input);
	}

	return (EXIT_SUCCESS);
}
