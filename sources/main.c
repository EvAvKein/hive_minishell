/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:27:53 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/27 22:24:15 by ekeinan          ###   ########.fr       */
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

void	test_dircontent()
{
	struct dirent	**dircontent = get_dircontent();
	if (!dircontent)
		printf("no dircontent\n");
	else
	{
		size_t	i = 0;
		while (dircontent[i])
			printf("%s\n", dircontent[i++]->d_name);
	}
	// free_str_arr(dircontent);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void) argc;
	(void) argv;
	init_shell(envp);
	test_dircontent();
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
