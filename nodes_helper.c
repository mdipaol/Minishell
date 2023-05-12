/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:34:45 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/12 16:21:47 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fd_manager(t_cmd *tmp, char **full_cmd)
{
	int	i;

	i = 0;
	while (full_cmd[i])
	{
		if (full_cmd[i][0] == '<' && full_cmd[i + 1] \
		&& full_cmd[i + 1][0] == '<')
		{
			tmp->in_fd = ft_get_fd(tmp, full_cmd + i, 0);
			i++;
		}
		else if (full_cmd[i][0] == '<')
			tmp->in_fd = ft_get_fd(tmp, full_cmd + i, 1);
		else if (full_cmd[i][0] == '>' && full_cmd[i + 1] \
		&& full_cmd[i + 1][0] == '>')
		{
			tmp->out_fd = ft_get_fd(tmp, full_cmd + i, 2);
			i++;
		}
		else if (full_cmd[i][0] == '>')
			tmp->out_fd = ft_get_fd(tmp, full_cmd + i, 3);
		i++;
	}
}

int	ft_cmd_clean_counter(char **full_cmd, int count, int i)
{
	while (full_cmd[i])
	{
		if (full_cmd[i][0] == '<' && full_cmd[i + 1] \
		&& full_cmd[i + 1][0] == '<')
			count++;
		else if (full_cmd[i][0] == '<')
			count += 2;
		else if (full_cmd[i][0] == '>' && full_cmd[i + 1] \
		&& full_cmd[i + 1][0] == '>')
			count++;
		else if (full_cmd[i][0] == '>')
			count += 2;
		i++;
	}
	return (i - count);
}

int	ft_get_fd(t_cmd *tmp, char **full_cmd, int flag)
{
	char	*path;

	path = ft_obtain_path(full_cmd, flag);
	ft_obtain_fd(tmp, path, flag);
	return (0);
}

char	**ft_cmd_cleaner(char **full_cmd)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	j = ft_cmd_clean_counter(full_cmd, i, j);
	new = malloc(sizeof(char *) * j + 1);
	new[j] = NULL;
	j = 0;
	while (full_cmd[i])
	{
		if (full_cmd[i][0] == '<' && full_cmd[i + 1] && full_cmd[i + 1][0] == '<')
			i += 3;
		else if (full_cmd[i][0] == '<')
			i += 2;
		else if (full_cmd[i][0] == '>' && full_cmd[i + 1] && full_cmd[i + 1][0] == '>')
			i += 3;
		else if (full_cmd[i][0] == '>')
			i += 2;
		else
			new[j++] = full_cmd[i++];
	}
	return (new);
}

void	ft_redirection(t_cmd **head)
{
	t_cmd	*tmp;
	char **path;


	tmp = *head;
	path = ft_split(getenv("PATH"), ':');
	while (tmp)
	{
		ft_fd_manager(tmp, tmp->full_cmd);
		tmp->full_cmd = ft_cmd_cleaner(tmp->full_cmd);
		tmp->full_path = ft_full_path_finder(tmp->full_cmd, path);
		if (tmp->full_path)
		printf("%s\n", tmp->full_path);
		tmp = tmp->next;
	}
}

