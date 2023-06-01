/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:27:04 by alegreci          #+#    #+#             */
/*   Updated: 2023/06/01 20:52:47 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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
 			free(envp[i]);
			envp[i] = ft_strdup(cmd);
			return (envp);
		}
		i++;
	}
	new_envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i++] = ft_strdup(cmd);
	new_envp[i] = NULL;
	ft_free_envp(envp);
	return (new_envp);
}

void	ft_export(char **full_cmd, t_data *data, int j)
{
	int	i;
	int	err;

	err = 0;
	i = j + 1;
	if (!full_cmd[j + 1])
		return ;
	while (full_cmd[i])
	{
		if (ft_strchr(full_cmd[i], '='))
		{
			if (full_cmd[i][0] == '=')
			{
				ft_error("export: '=': not a valid identifier\n", 1);
				err = 1;
			}
			else
				data->envp = ft_set_export(full_cmd[i], data->envp, i, 0);
		}
		i++;
	}
	if (!err)
		g_status = 0;
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
		{
			free(envp[i]);
			envp[i] = ft_strjoin("PWD=", pwd);
		}
		else if (!ft_strncmp(envp[i], "OLDPWD=", 7))
		{
			free(envp[i]);
			envp[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
		i++;
	}
	free(pwd);
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
		ft_error("Minishem: cd: No such file or directory\n", 1);
	free(path);
}

void	ft_cd(char **full_cmd, char **envp, int j)
{
	char	*s;
	char	*pwd;

	(void)envp;
	(void)s;
	if (!full_cmd[j + 1])
		return ;
	s = full_cmd[j + 1];
	if (full_cmd[j + 1] && full_cmd[j + 2])
	{
		ft_error("Minishem: cd: Too many arguments\n", 1);
		return ;
	}
	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	ft_chdir(s, pwd);
	ft_set_env(pwd, envp);
	free(pwd);
	g_status = 0;
}
