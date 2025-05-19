/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:31:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/19 08:46:17 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Initializes the program's signal handlers/actions.
 * 
 */
void init_signal_handlers()
{
	// rl_event_hook can also be assigned a handler, might be useful for heredoc
	sigaction(SIGINT, 
		&(struct sigaction){.sa_sigaction = sigint_handler}, NULL);
	sigaction(SIGPIPE,
		&(struct sigaction){.sa_sigaction = sigpipe_handler}, NULL);
	sigaction(SIGQUIT,
		&(struct sigaction){.sa_handler = SIG_IGN}, NULL);
}

/**
 * 
 * A signal handler for SIGINT -
 * displays a new prompt and updates the exist status.
 * 
 * @param sig     Ignored.
 * 
 * @param info    Ignored.
 * 
 * @param prevact Ignored.
 * 
 */
void	sigint_handler(int sig, siginfo_t *info, void *prevact)
{
	(void)prevact;
	(void)info;
	(void)sig;

	get_shell()->last_exit_status = 128 + SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * 
 * A signal handler for SIGPIPE -
 * exits the process after printing an error message and freeing heap memory.
 * 
 * @param sig     Ignored.
 * 
 * @param info    Ignored.
 * 
 * @param prevact Ignored.
 * 
 */
void	sigpipe_handler(int sig, siginfo_t *info, void *prevact)
{
	char	buffer[20];

	(void)prevact;
	(void)info;
	(void)sig;
	
	print_err(pid_to_buf(buffer),
		" process received SIGPIPE - exiting gracefully.");
	shell_exit(get_shell(), 128 + SIGPIPE);
}

/**
 * 
 * A signal handler for heredoc's SIGINT -
 * exits out of heredoc.
 * 
 * @param sig     Ignored.
 * 
 * @param info    Ignored.
 * 
 * @param prevact Ignored.
 * 
 */
void	heredoc_sigint_handler(int sig, siginfo_t *info, void *prevact)
{
	(void)prevact;
	(void)info;
	(void)sig;
	
	get_shell()->last_exit_status = 128 + SIGINT;
	close(STDIN_FILENO);
}
