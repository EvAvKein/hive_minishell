/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:16:31 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/07 12:51:57 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    execute_command(t_shell *shell)
{
    if (is_builtin(shell->nodes->argv[0]))
    {
        if (execute_builtin(shell) == 1)
        {
            //shell->last_exit_status = ??;
            return (1);
        }
        //shell->last_exit_status == ??;
    }
    else
    {
        if (fork_and_execute_sys_command(shell) == 1)
            return (1);
    }
    return (0);
}

int    count_commands(t_node *head)
{
    t_node    *tmp;
    int        count;
    
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

int    count_redirections(t_node *head)
{
    t_node    *tmp;
    int        count;
    
    tmp = head;
    count = 0;
    while (tmp->next && tmp->next != head)
    {
        if (tmp->type == INFILE || tmp->type == OUTFILE || tmp->type == APPENDFILE)
            count++;
        tmp = tmp->next;
    }
    if (tmp->type == INFILE || tmp->type == OUTFILE || tmp->type == APPENDFILE)
        count++;
    return (count);
}

void    execution(t_shell *shell)
{
    int        command_count;
    t_exec    *exec;
    int        redirections;

    command_count  = count_commands(shell->nodes);
    redirections = count_redirections(shell->nodes);
    exec = ft_calloc(1, sizeof(t_exec));
    if (!exec)
        fatal_error(shell, "execution: malloc failed");
    shell->exec = exec;
    if (command_count == 1 && !redirections)
        execute_command(shell);
    else
        execute_pipeline(shell);
    free(exec);
}