/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:34:45 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/30 15:50:58 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fd_manager(t_cmd *tmp, char **full_cmd)
{
	int	i;

	i = 0;
	while (full_cmd[i])
	{
		if (!ft_strncmp(full_cmd[i], "<", 2) && full_cmd[i + 1] \
		&& !ft_strncmp(full_cmd[i + 1], "<", 2))
		{
			ft_get_fd(tmp, full_cmd + i, 0);
			i++;
		}
		else if (!ft_strncmp(full_cmd[i], "<", 2))
			ft_get_fd(tmp, full_cmd + i, 1);
		else if (!ft_strncmp(full_cmd[i], ">", 2) && full_cmd[i + 1] \
		&& !ft_strncmp(full_cmd[i + 1], ">", 2))
		{
			ft_get_fd(tmp, full_cmd + i, 2);
			i++;
		}
		else if (!ft_strncmp(full_cmd[i], ">", 2))
			ft_get_fd(tmp, full_cmd + i, 3);
		i++;
	}
}

int	ft_cmd_clean_counter(char **full_cmd, int count, int i)
{
	while (full_cmd[i])
	{
		if (!ft_strncmp(full_cmd[i], "<", 2) && full_cmd[i + 1] \
		&& !ft_strncmp(full_cmd[i + 1], "<", 2))
			count++;
		else if (!ft_strncmp(full_cmd[i], "<", 2))
			count += 2;
		else if (!ft_strncmp(full_cmd[i], ">", 2) && full_cmd[i + 1] \
		&& !ft_strncmp(full_cmd[i + 1], ">", 2))
			count++;
		else if (!ft_strncmp(full_cmd[i], ">", 2))
			count += 2;
		i++;
	}
	return (i - count);
}

void	ft_get_fd(t_cmd *tmp, char **full_cmd, int flag)
{
	char	*path;

	path = ft_obtain_path(full_cmd, flag);
	ft_obtain_fd(tmp, path, flag);
}

char	**ft_cmd_cleaner(char **full_cmd)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	j = ft_cmd_clean_counter(full_cmd, i, j);
	new = malloc(sizeof(char *) * (j + 1));
	new[j] = NULL;
	j = 0;
	while (full_cmd[i])
	{
		if (!ft_strncmp(full_cmd[i], "<", 2) && full_cmd[i + 1] \
		&& !ft_strncmp(full_cmd[i + 1], "<", 2) && full_cmd[i + 2])
			i += 3;
		else if (!ft_strncmp(full_cmd[i], "<", 2) && full_cmd[i + 1])
			i += 2;
		else if (!ft_strncmp(full_cmd[i], ">", 2) && full_cmd[i + 1] \
		&& !ft_strncmp(full_cmd[i + 1], ">", 2) && full_cmd[i + 2])
			i += 3;
		else if (!ft_strncmp(full_cmd[i], ">", 2) && full_cmd[i + 1])
			i += 2;
		else
			new[j++] = full_cmd[i++];
	}
	ft_free_redirect(full_cmd);
	free (full_cmd);
	return (new);
}

void	ft_redirection(t_cmd **head)
{
	t_cmd	*tmp;
	char	**path;
	int		i;

	i = 0;
	tmp = *head;
	path = ft_split(getenv("PATH"), ':');
	while (tmp)
	{
		ft_fd_manager(tmp, tmp->full_cmd);
		tmp->full_cmd = ft_cmd_cleaner(tmp->full_cmd);
		tmp->full_cmd = ft_negative_restorer(tmp->full_cmd);
		tmp->full_path = ft_full_path_finder(tmp->full_cmd, path);
		tmp = tmp->next;
	}
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
