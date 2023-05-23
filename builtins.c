/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:06:20 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/23 14:53:52 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	ft_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	getcwd(s, sizeof(s));
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	free(s);
	g_status = 0;
}

void	ft_echo(char **full_cmd)
{
	int	i;
	int	flag;
	int	new;

	i = 1;
	flag = 0;
	new = 1;
	while (full_cmd[i])
	{
		if (!flag && !ft_strncmp(full_cmd[i], "-n", 2) && \
		(ft_char_counter(full_cmd[i], 'n') == (int)ft_strlen(full_cmd[i]) - 1))
			new = 0;
		else
		{
			flag = 1;
			write(1, full_cmd[i], ft_strlen(full_cmd[i]));
			if (full_cmd[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (new)
		write(1, "\n", 1);
	g_status = 0;
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	g_status = 0;
}

void	ft_builtin(t_cmd *tmp, char ***envp, t_data *data)
{
	if (ft_strncmp(tmp->full_cmd[0], "echo", 5) == 0)
		ft_echo(tmp->full_cmd);
	else if (ft_strncmp(tmp->full_cmd[0], "cd", 2) == 0)
		ft_cd(tmp->full_cmd, *envp);
	else if (ft_strncmp(tmp->full_cmd[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(tmp->full_cmd[0], "export", 6) == 0)
		ft_export(tmp->full_cmd, envp);
	else if (ft_strncmp(tmp->full_cmd[0], "unset", 5) == 0)
		ft_unset(tmp->full_cmd, envp);
	else if (ft_strncmp(tmp->full_cmd[0], "env", 3) == 0)
		ft_env(*envp);
	else if (ft_strncmp(tmp->full_cmd[0], "exit", 4) == 0)
		ft_exit(tmp->full_cmd, data);
}

int	ft_is_builtin(char *full_cmd)
{
	if (ft_strncmp(full_cmd, "echo", 6) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "exit", 5) == 0)
		return (1);
	return (0);
}
