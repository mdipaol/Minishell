/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:47:21 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/18 19:21:38 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_unset(char **envp, int i, char *cmd)
{
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], cmd, ft_strlen(cmd)))
			return (0);
		i++;
	}
	return (1);
}

char	**ft_unset_envp(char *full_cmd, char **envp, int j)
{
	int		i;
	char	**new_envp;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin(full_cmd, "=");
	free(full_cmd);
	if (ft_check_unset(envp, i, cmd))
		return (envp);
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], cmd, ft_strlen(cmd)))
			new_envp[j++] = envp[i];
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

void	ft_unset(char **cmd, char ***envp)
{
	int	i;

	i = 1;
	if (!cmd[1])
		return ;
	while (cmd[i])
	{
		*envp = ft_unset_envp(cmd[i], *envp, 0);
		i++;
	}
}
