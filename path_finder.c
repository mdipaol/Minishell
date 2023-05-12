/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:57:57 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/12 16:06:37 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_full_path_finder(char **full_cmd, char **path)
{
	int		i;
	char	*cmd;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, full_cmd[0]);
		free(tmp);
		if (access(cmd, F_OK) == 0)
			break ;
		i++;
		free(cmd);
	}
	if (!path[i])
	{
		write(2, "command not found\n", 18);
		cmd = NULL;
	}
	return (cmd);
}
