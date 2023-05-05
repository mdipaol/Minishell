/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:34:45 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/05 15:09:58 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fd_manager(t_cmd *tmp, char **full_cmd)
{
	int	i;

	i = 0;
	while (full_cmd[i])
	{
		if (full_cmd[i][0] == '<' && full_cmd[i + 1] && full_cmd[i + 1][0] == '<')
		{
			tmp->in_fd = ft_get_fd(tmp, full_cmd + i, 0);
			i++;
		}
		else if (full_cmd[i][0] == '<')
			tmp->in_fd = ft_get_fd(tmp, full_cmd + i, 1);
		else if (full_cmd[i][0] == '>' && full_cmd[i + 1] && full_cmd[i + 1][0] == '>')
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
		if (full_cmd[i][0] == '<' && full_cmd[i + 1] && full_cmd[i + 1][0] == '<')
			count++;
		else if (full_cmd[i][0] == '<')
			count += 2;
		else if (full_cmd[i][0] == '>' && full_cmd[i + 1] && full_cmd[i + 1][0] == '>')
			count++;
		else if (full_cmd[i][0] == '>')
			count += 2;
		i++;
	}
	printf("count :%d, i : %d", count, i);
	return (i - count);
}

int	ft_get_fd(t_cmd *tmp, char **full_cmd, int flag)
{
	if (full_cmd)
		return (flag);
	else
		return (tmp->in_fd);
	/* DA IMPLEMENTARE :
		IN BASE AL TIPO DI FLAG CHE E' ARRIVATA APRE IL FILE DESCRIPTOR
		E LO RITORNA, SE ARRIVA FLAG = 0 HEREDOC.
	*/
}

char	**ft_cmd_cleaner(char **full_cmd)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * ft_cmd_clean_counter(full_cmd, i, j) + 1);
	if (full_cmd)
		return (full_cmd);
	else
		return (new);

}

void	ft_redirection(t_cmd **head)
{
	t_cmd	*tmp;

	tmp = *head;
	while (tmp)
	{
		ft_fd_manager(tmp, tmp->full_cmd);
		tmp->full_cmd = ft_cmd_cleaner(tmp->full_cmd);
		tmp = tmp->next;
	}
}

