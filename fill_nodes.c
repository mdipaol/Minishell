/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:22:15 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/22 19:15:18 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_all_cmd_init(char ***all, int n, char **trim)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	all[n] = NULL;
	while (i < n)
	{
		k = 0;
		while (trim[j] && trim[j][0] != '|')
		{
			k++;
			j++;
		}
		all[i] = malloc(sizeof(char *) * (k + 1));
		all[i][k] = NULL;
		i++;
		j++;
	}
}

char	***ft_fill_all_cmd(char ***all, int n, char **trim)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < n)
	{

		k = 0;
		while (trim[j] && trim[j][0] != '|')
		{
			all[i][k] = trim[j];
			k++;
			j++;
		}
		i++;
		j++;
	}

	return (all);
}

void	ft_node_init(t_cmd **head, int n, char ***all_cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 1;
	*head = malloc(sizeof(t_cmd));
	tmp = *head;
	(*head)->in_fd = 0;
	(*head)->out_fd = 1;
	(*head)->full_cmd = all_cmd[0];
	(*head)->next = NULL;
	while (i < n)
	{
		(*head)->next = malloc(sizeof(t_cmd));
		*head = (*head)->next;
		(*head)->in_fd = 0;
		(*head)->out_fd = 1;
		(*head)->full_cmd = all_cmd[i];
		(*head)->next = NULL;
		i++;
	}
	*head = tmp;
}

int	ft_count_nodes(char **s)
{
	int	count;
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	count = 1;
	while (s[i])
	{
		if (ft_strchr(s[i], '|'))
		{
			if ((!s[i + 1] || ft_strchr(s[i + 1], '|')) && !flag)
			{
				ft_error(\
				"Minishem: syntax error near unexpected token '|'\n", 1);
				flag = 1;
			}
			count++;
		}
		i++;
	}
	return (count);
}

t_cmd	**ft_fill_nodes(t_data *data)
{
	t_cmd	**head;
	int		cmd_n;
	char	***all_cmd;

	head = malloc(sizeof(t_cmd *));
	cmd_n = ft_count_nodes(data->cmd_trim);
	all_cmd = malloc(sizeof(char **) * (cmd_n + 1));
	ft_all_cmd_init(all_cmd, cmd_n, data->cmd_trim);
	all_cmd = ft_fill_all_cmd(all_cmd, cmd_n, data->cmd_trim);
	ft_node_init(head, cmd_n, all_cmd);
	ft_redirection(head);
	free (all_cmd);
	return (head);
}
