/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:34:45 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/02 15:26:25 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_clean_counter(char **full_cmd, int count, int i)
{
	while (full_cmd[i])
		i++;
	i--;
	if (full_cmd[0][0] == '<' && full_cmd[1] && full_cmd[1][0] == '<')
		count += 3;
	else if (full_cmd[0][0] == '<')
		count += 2;
	if (full_cmd[i][0] == '>' && i > 0 && full_cmd[i - 1][0] == '>')
		count += 3;
	else if (full_cmd[i][0] == '>')
		count += 2;
	return ((i + 1) - count);
}

int	ft_get_fd(char **full_cmd, int flag)
{
	if (full_cmd)
		return (0);
	else
		return (flag);
	/* DA IMPLEMENTARE :
		IN BASE AL TIPO DI FLAG CHE E' ARRIVATA APRE IL FILE DESCRIPTOR
		E LO RITORNA, SE ARRIVA FLAG = 2 HEREDOC.
	*/
}

char	**ft_cmd_cleaner(char **full_cmd)
{
	int		i;
	int		j;
	char	**new;

	j = 0;
	i = 0;
	new = malloc(sizeof(char *) * (ft_cmd_clean_counter(full_cmd, i, j) + 1));
	printf("%d", ft_cmd_clean_counter(full_cmd, i, j));
	new[ft_cmd_clean_counter(full_cmd, i, j)] = NULL;
/* 	while (full_cmd[i])
	{
		if (full_cmd[i][0] == '|')
			i++;
		else if (full_cmd[i][0] == '>' && full_cmd[i + 1] && full_cmd[i + 1][0] == '>')
			i += 2;
		else if (full_cmd[i][0] == '>')
			i++;
		else if (full_cmd[i][0] == '<' && full_cmd[i + 1] && full_cmd[i + 1][0] == '<')
			i = i;
		else if (full_cmd[i][0] == '<')
			i += 2;
		else
			new[j++] = full_cmd[i++];
	} */
	return (new);
}

void	ft_redirection(t_cmd **head)
{
	t_cmd	*tmp;
	int		i;

	tmp = *head;
	while (tmp)
	{
		i = 0;
		if (tmp->full_cmd[0][0] == '<' && tmp->full_cmd[1][0] == '<')
			tmp->in_fd = ft_get_fd(tmp->full_cmd, 0);
		else if (tmp->full_cmd[0][0] == '<')
			tmp->in_fd = ft_get_fd(tmp->full_cmd, 1);
		while (tmp->full_cmd[i])
			i++;
		if (i > 1 && tmp->full_cmd[i - 1][0] == '>' && tmp->full_cmd[i - 2][0] == '>')
			tmp->out_fd = ft_get_fd(tmp->full_cmd, 2);
		else if (i > 0 && tmp->full_cmd[i - 1][0] == '>')
			tmp->out_fd = ft_get_fd(tmp->full_cmd, 3);
		tmp->full_cmd = ft_cmd_cleaner(tmp->full_cmd);
		tmp = tmp->next;
	}
}

