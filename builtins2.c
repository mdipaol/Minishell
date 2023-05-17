/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:27:04 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/17 19:37:05 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env(char *old_pwd, char **envp)
{
	int	i;
	char *pwd;

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
