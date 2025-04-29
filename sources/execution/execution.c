/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/12 13:16:07 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_command_child(t_shell *shell, t_node *current)
{
	//if (check_redirections(current) == 1)
	//	exit(EXIT_FAILURE);
	if (current->type == COMMAND)
	{
		if (execute_sys_command(shell, current) == 1)
		{
			exit(EXIT_FAILURE);
			shell->last_exit_status = 1;
		}
	}
	shell->last_exit_status = 0;
	exit(EXIT_SUCCESS);
}

int	execute_command(t_shell *shell, t_node *current)
{
	int		pid;
	int		status;

	if (is_builtin(current->argv[0]))
	{
		if (execute_builtin(shell) == 1)
		{
			shell->last_exit_status = 1;
			return (1);
		}
		shell->last_exit_status = 0;
		return (0);
	}
	pid = fork();
	if (pid == 0)
		single_command_child(shell, current);
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			shell->last_exit_status = 1;
		}
		else
			shell->last_exit_status = WEXITSTATUS(status);
	}
	else if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	return (0);
}

int	count_commands(t_node *head)
{
	t_node	*tmp;
	int		count;
	
	tmp = head;
	count = 0;
	while (tmp->next && tmp->next != head)
	{
		if (tmp->type == COMMAND)
			count++;
		tmp = tmp->next;
	}
	if (tmp->type == COMMAND)
		count++;
	return (count);
}

void	single_command(t_shell *shell)
{
	t_node *current;

	current = shell->nodes;
	while(current)
	{
		if (current->type == COMMAND)
		{
			if (execute_command(shell, current) == 1)
			{
				perror("system comand failed");
				return ;
			}
		}
		current = current->next;
	}
}

int	count_commands(t_node *head)
{
	t_node	*tmp;
	int		count;
	
	tmp = head;
	count = 0;
	while (tmp->next && tmp->next != head)
	{
		if (tmp->type == COMMAND)
			count++;
		tmp = tmp->next;
	}
	if (tmp->type == COMMAND)
		count++;
	return (count);
}

void	execution(t_shell *shell)
{
	int		command_count;
	t_exec	*exec;
	int		redirections;

	command_count  = count_commands(shell->nodes);
	redirections = count_redirections(shell->nodes);
	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		fatal_error(shell, "execution: malloc failed");
	shell->exec = exec;
	//open_redirections() -> dont dup them yet
	if (command_count == 1)
		single_command(shell); //maybe doesnt matter
	else
		execute_pipeline(shell);
	free(exec);
}
