/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:37 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/26 15:16:48 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}

int	ms_pwd(char **envp)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = get_pwd_from_env(envp);//varmista ett dupppaat ton tonne ettei tuu double free
		if (!path)
		{
			print_err("pwd: ", "getcwd failed");
			return (1);
		}
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

static int	check_flag(t_node *command)
{
	if (command->argv[1] && command->argv[1][0] == '-'
		&& command->argv[1][1] && command->argv[1][1] == 'n')
		return (1);
	else
		return (0);
}

int	ms_echo(t_node *command)
{
	int	i;
	int	flag;

	i = 1;
	flag = check_flag(command);
	if (flag)
		i++;
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

void	ms_exit(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->nodes->argc > 1)
		printf("exit\n");
	if (shell->nodes->argv[1])
	{
		while (shell->nodes->argv[1][i])
		{
			if (!ft_isdigit(shell->nodes->argv[1][i])
			|| ft_atoll(shell->nodes->argv[1]) > INT_MAX
			|| ft_atoll(shell->nodes->argv[1]) < 0)
			{
				print_err("exit: ", "numeric value required");
				return ;
			}
			i++;
		}
		shell->last_exit_status = ft_atoi(shell->nodes->argv[1]);//atoi_longlong better?
	}
	shell_exit(shell->last_exit_status);
}
