/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:57:57 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/31 19:01:25 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_full_path_finder(char **full_cmd, char **path)
{
	int		i;
	int		j;
	char	*cmd;
	char	*tmp;

	i = 0;
	j = 0;
	while (full_cmd[j] && !full_cmd[j][0])
		j++;
	if (!full_cmd[j] || ft_is_builtin(full_cmd[j]))
		return (NULL);
	if (ft_strchr(full_cmd[j], '/'))
	{
		if (access(full_cmd[j], X_OK) == 0)
			return (full_cmd[j]);
		if (access(full_cmd[j], F_OK) == -1)
			ft_error("Minishell: No such file or directory\n", 127);
		else if (access(full_cmd[j], X_OK) == -1)
			ft_error("Minishell: Permission denied\n", 126);
		return (NULL);
	}
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, full_cmd[j]);
		free(tmp);
		if (access(cmd, X_OK) == 0)
			break ;
		i++;
		free(cmd);
	}
	if (!path[i])
	{
		ft_error("Minishem: Command not found\n", 127);
		cmd = NULL;
	}
	return (cmd);
}
