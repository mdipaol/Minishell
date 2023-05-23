/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:47:21 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/23 15:00:14 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	ft_exit(char **cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		ft_error(NULL, 0);
	else if (i > 2)
		ft_error("exit: too many arguments\n", 1);
	else if (i == 2)
	{
		if (!ft_numstr(cmd[1]))
			ft_error("exit: numeric argument required\n", 2);
		else
			ft_error(NULL, ft_atoi(cmd[1]) % 256);
	}
	if (i <= 2)
		data->run = 0;
}

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
	g_status = 0;
}
