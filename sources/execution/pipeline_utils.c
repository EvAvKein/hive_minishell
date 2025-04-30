/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:08:39 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/12 13:20:44 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_all_children(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->exec->pid_count)
	{
		waitpid(shell->exec->pids[i], &status, 0);
		if (i == shell->exec->pid_count - 1)
		{
			if (WIFEXITED(status)) // child process exited normally
				shell->last_exit_status = WEXITSTATUS(status);
			else // child process was terminated by signal or error
				shell->last_exit_status = 1;
		}
		i++;
	}
}

void    execute_last_pipeline_element(t_shell *shell, t_node *current,
        int prev_fd, int pipe_fd[2])
{
    pid_t   pid;

    pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		pipeline_child(shell, current, prev_fd, pipe_fd);
	else
	{
		shell->exec->pids[shell->exec->pid_count++] = pid;
        if (prev_fd != -1)
			close(prev_fd);
    }
}

int *close_pipe_fds(int pipe_fd[2])
{
    if (pipe_fd[WRITE] != -1)
        close(pipe_fd[WRITE]);//close the WRITE end of the pipe because it's been redirected
    if (pipe_fd[READ] != -1)
        close(pipe_fd[READ]);// close the READ end of the pipe (because it's unused)
    return(pipe_fd);
}
