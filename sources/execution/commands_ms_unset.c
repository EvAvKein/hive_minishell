/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ms_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:32:49 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/14 11:45:28 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	line_is_removable(char *line, char **remove)
{
	int	i;

	i = 0;
	while (remove[i])
	{
		if (!ft_strncmp(line, remove[i], ft_strlen(remove[i])))
			return (1);
		i++;
	}
	return (0);
}

static char **set_removables(t_shell *shell)
{
	char **ret;
	int	i;
	int	k;

	i = 0;
	k = 1;
	ret = ft_calloc(shell->nodes->argc, sizeof(char *));
	if (!ret)
	{
		printf("Error!"); //TODO
		return (NULL);
	}
	while (shell->nodes->argv[k])
	{
		ret[i] = shell->nodes->argv[k];
		i++;
		k++;
	}
	return (ret);
}

void	ms_unset(t_shell *shell)
{
	int		i;
	int		k;
	char	**remove;

	i = 0;
	k = 0;
	shell->env_dup = ft_calloc(get_env_elements(shell->env), sizeof(char *));
	if (!shell->env_dup)
		printf("Error!"); //TODO
	remove = set_removables(shell);
	if (!remove)
		printf("Error!"); //TODO
	while (shell->env[i])
	{
		if (!line_is_removable(shell->env[i], remove))
		{
			shell->env_dup[k] = shell->env[i];
			i++;
			k++;
		}
		else
			i++;
	}
}

/*int main(int argc, char **argv, char **envp)
{
	argc = 2;
	argv = NULL;
	t_shell *shell;
	shell = NULL;
	shell->env = envp;
	shell->nodes->argc = 1;
	shell->nodes->argv[0] = "MAIL";
	ms_unset(shell);
}*/
