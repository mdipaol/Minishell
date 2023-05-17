/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:06:20 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/16 18:50:49 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char *s = getenv("PWD");
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

void	ft_export(t_cmd *tmp, char **envp)
{
	int	i;
	char **env = __environ;

	(void)envp;
	i = 0;
	if (!tmp->full_cmd[1])
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}

}

void	ft_builtin(t_cmd *tmp, char **envp)
{

	/* if (ft_strncmp(tmp->full_cmd, "echo", 5) == 0)
		ft_echo(tmp);
	else if (ft_strncmp(tmp->full_cmd, "cd", 2) == 0)
		ft_cd(tmp); */
	if (ft_strncmp(tmp->full_cmd[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(tmp->full_cmd[0], "export", 6) == 0)
		ft_export(tmp, envp);
	else if (ft_strncmp(tmp->full_cmd, "unset", 5) == 0)
		ft_unset(tmp);
	else if (ft_strncmp(tmp->full_cmd, "env", 3) == 0)
		ft_env(tmp);
	else if (ft_strncmp(tmp->full_cmd, "exit", 4) == 0)
		ft_exit(tmp);
	exit(1);
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

