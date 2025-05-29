/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:32:49 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/29 18:24:05 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(t_node *command)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (command->argv[i])
	{
		if (command->argv[i][0] == '-' && command->argv[i][1] == 'n')
		{
			flag++;
			if (command->argv[i][2] != 'n' && command->argv[i][2] != '\0')
				flag = 0;
		}
		i++;
	}
	return (flag);
}

int	ms_echo(t_node *command)
{
	int	i;
	int	flag;

	i = 1;
	flag = check_flag(command);
	if (flag)
		i += flag;
	if (flag && command->argc == 2)
		return (0);
	if (command->argc == 1)
	{
		printf("\n");
		return (0);
	}
	while (command->argv[i])
	{
		printf("%s", command->argv[i]);
		i++;
		if (i < command->argc)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}

static void	handle_exit_argument(t_shell *shell, t_node *command)
{
	int	i;

	i = 0;
	if (ft_atoll(command->argv[1]) > INT_MAX
		|| ft_atoll(command->argv[1]) < 0)
	{
		print_err("exit: ", "numeric argument required");
		shell->last_exit_status = 2;
		shell_exit(shell->last_exit_status);
	}
	while (command->argv[1][i])
	{
		if (!ft_isdigit(command->argv[1][i]))
		{
			print_err("exit: ", "numeric argument required");
			shell->last_exit_status = 2;
			shell_exit(shell->last_exit_status);
		}
		i++;
	}
}

void	ms_exit(t_shell *shell, t_node *command)
{
	if (command->argc > 2)
	{
		print_err("exit: ", "too many arguments");
		return ;
	}
	if (command->argc == 1)
		printf("exit\n");
	if (command->argv[1])
	{
		handle_exit_argument(shell, command);
		shell->last_exit_status = ft_atoi(command->argv[1]);
	}
	shell_exit(shell->last_exit_status);
}
