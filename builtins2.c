/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:27:04 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/18 18:46:51 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_set_export(char *cmd, char **envp, int i, int id)
{
	char	**new_envp;

	id = 0;
	i = 0;
	while (cmd[id] != '=')
		id++;
	while (envp[i])
	{
		if (!ft_strncmp(cmd, envp[i], id + 1))
		{
			envp[i] = cmd;
			return (envp);
		}
		i++;
	}
	new_envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i++] = cmd;
	new_envp[i] = NULL;
	return (new_envp);
}

void	ft_export(char **full_cmd, char ***envp)
{
	int	i;

	i = 1;
	if (!full_cmd[1])
		return ;
	while (full_cmd[i])
	{
		if (ft_strchr(full_cmd[i], '='))
		{
			if (full_cmd[i][0] == '=')
				write(2, "export: `=': not a valid identifier\n", 36);
			else
				*envp = ft_set_export(full_cmd[i], *envp, i, 0);
		}
		i++;
	}
}

void	ft_set_env(char *old_pwd, char **envp)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
			envp[i] = ft_strjoin("PWD=", pwd);
		else if (!ft_strncmp(envp[i], "OLDPWD=", 7))
			envp[i] = ft_strjoin("OLDPWD=", old_pwd);
		i++;
	}
}

void	ft_chdir(char *path, char *pwd)
{
	if (!ft_strchr(path, '/'))
	{
		pwd = ft_strjoin(pwd, "/");
		path = ft_strjoin(pwd, path);
		free(pwd);
	}
	if (chdir(path) == -1)
		write(2, "error\n", 6);
}

void	ft_cd(char **full_cmd, char **envp)
{
	char	*s;
	char	*pwd;

	(void)envp;
	(void)s;
	if (!full_cmd[1])
		return ;
	s = full_cmd[1];
	if (full_cmd[1] && full_cmd[2])
	{
		write(2, "cd: string not in pwd:", 22);
		write(2, full_cmd[1], ft_strlen(full_cmd[1]));
		write(1, "\n", 1);
	}
	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	ft_chdir(s, pwd);
	ft_set_env(pwd, envp);
	free(pwd);
}
