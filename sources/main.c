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
	
	(void) argc;
	(void) argv;
	(void) envp;

	ft_bzero(&shell, sizeof(t_shell));

	while (1)
	{
		shell.latest_input = readline("shellGBTQ+ >");
		if (!shell.latest_input || !shell.latest_input[0])
			continue;
		add_history(shell.latest_input);
		parsing(&shell);
		execution(&shell);
	}

	return (EXIT_SUCCESS);
}
