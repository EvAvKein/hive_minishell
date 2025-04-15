/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ms_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:32:49 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/15 11:43:23 by ahavu            ###   ########.fr       */
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
	char	**new_env;

	i = 0;
	k = 0;
	remove = set_removables(shell);
	new_env = ft_calloc(get_env_elements(shell->ms_envp) + 1, sizeof(char *));
	if (!remove || !new_env)
		printf("Error!"); //TODO
	while (shell->ms_envp[i])
	{
		if (!line_is_removable(shell->ms_envp[i], remove))
		{
			new_env[k] = ft_strdup(shell->ms_envp[i]);
			k++;
		}
		i++;
	}
	new_env[k] = NULL;
	free_env_array(shell->ms_envp);
	shell->ms_envp = new_env;
	free(remove);
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
