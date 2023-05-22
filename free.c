/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:53:47 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/22 19:08:23 by mdi-paol         ###   ########.fr       */
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
	ft_free_all_2(data);
	if (data->cmds)
		free (data->cmds);
	unlink("/tmp/.heredoc");
}
