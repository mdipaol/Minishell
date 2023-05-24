/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:57:57 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/24 16:50:43 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_full_path_finder(char **full_cmd, char **path)
{
	int		i;
	char	*cmd;
	char	*tmp;

	i = 0;
	if (!full_cmd[0] || ft_is_builtin(full_cmd[0]))
		return (NULL);
	if (ft_strchr(full_cmd[0], '/'))
	{
		if (access(full_cmd[0], X_OK) == 0)
			return (full_cmd[0]);
		if (access(full_cmd[0], F_OK) == -1)
			ft_error("Minishell: No such file or directory\n", 127);
		else if (access(full_cmd[0], X_OK) == -1)
			ft_error("Minishell: Permission denied\n", 126);
		return (NULL);
	}
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, full_cmd[0]);
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
