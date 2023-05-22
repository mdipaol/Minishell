/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:57:57 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/22 17:18:29 by mdi-paol         ###   ########.fr       */
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
		return (full_cmd[0]);
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
