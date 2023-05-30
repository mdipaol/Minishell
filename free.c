/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:53:47 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/30 17:55:20 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all_2(t_data *data)
{
	(void)data;
/* 	int	i;

	i = 0;
	while (data->cmd_trim[i])
	{
		free(data->cmd_trim[i]);
		i++;
	} */
/* 	if (data->cmd_trim)
		free(data->cmd_trim); */
}

void	ft_free_all(t_data *data)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;
	int		i;

	if (data->split_error)
		return ;
	tmp = *data->cmds;
	while (tmp)
	{
		i = 0;
		while (tmp->full_cmd && tmp->full_cmd[i])
		{
			free(tmp->full_cmd[i]);
			i++;
		}
		if (tmp->full_cmd)
			free(tmp->full_cmd);
		if (tmp->full_path)
			free(tmp->full_path);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}

/* 	ft_free_all_2(data); */
	//if (data->cmds)
	free (data->cmds);
	unlink("/tmp/.heredoc");
}

int	ft_free_redirect_count(char **full_cmd, int i, int n)
{
	if (n == 3)
	{
		free(full_cmd[i]);
		free(full_cmd[i + 1]);
		free(full_cmd[i + 2]);
		return (i + 3);
	}
	if (n == 2)
	{
		free(full_cmd[i]);
		free(full_cmd[i + 1]);
		return (i + 2);
	}
	return (i);
}

void	ft_free_redirect(char **full_cmd)
{
	int	i;

	i = 0;
	while (full_cmd[i])
	{
		if (!ft_strncmp(full_cmd[i], "<", 2) && full_cmd[i + 1] \
		&& !ft_strncmp(full_cmd[i + 1], "<", 2) && full_cmd[i + 2])
			i = ft_free_redirect_count(full_cmd, i, 3);
		else if (!ft_strncmp(full_cmd[i], "<", 2) && full_cmd[i + 1])
			i = ft_free_redirect_count(full_cmd, i, 2);
		else if (!ft_strncmp(full_cmd[i], ">", 2) && full_cmd[i + 1] \
		&& !ft_strncmp(full_cmd[i + 1], ">", 2) && full_cmd[i + 2])
			i = ft_free_redirect_count(full_cmd, i, 3);
		else if (!ft_strncmp(full_cmd[i], ">", 2) && full_cmd[i + 1])
			i = ft_free_redirect_count(full_cmd, i, 2);
		else
			i++;
	}
}

t_cmd	*ft_free_nodes(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = cmd;
	cmd = cmd->next;
	while (tmp->full_cmd && tmp->full_cmd[i])
	{
		free(tmp->full_cmd[i]);
		i++;
	}
	if (tmp->full_cmd)
		free(tmp->full_cmd);
	if (tmp->full_path)
		free(tmp->full_path);
	free(tmp);
	return (cmd);
}
