/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:22:15 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/26 12:37:12 by mdi-paol         ###   ########.fr       */
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
		while (trim[j] && ft_strncmp(trim[j], "|", 2))
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
		while (trim[j] && ft_strncmp(trim[j], "|", 2))
		{
			all[i][k] = trim[j];
			k++;
			j++;
		}
		if (trim[j] && !ft_strncmp(trim[j], "|", 2))
			free(trim[j]);
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
	tmp->in_fd = 0;
	tmp->out_fd = 1;
	tmp->full_cmd = all_cmd[0];
	tmp->next = NULL;
	while (i < n)
	{
		tmp->next = malloc(sizeof(t_cmd));
		tmp = tmp->next;
		tmp->in_fd = 0;
		tmp->out_fd = 1;
		tmp->full_cmd = all_cmd[i];
		tmp->next = NULL;
		i++;
	}
	/* *head = tmp; */
}

int	ft_count_nodes(char **s, t_data *data)
{
	int	count;
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	count = 1;
	data->pipe_stop = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], "|", 2))
		{
			if ((!s[i + 1] || !ft_strncmp(s[i + 1], "|", 2) || s[0][0] == '|') && !flag)
			{
				ft_error(\
				"Minishem: syntax error near unexpected token '|'\n", 1);
				flag = 1;
			}
			count++;
		}
		i++;
	}
	if (s[0][0] == '|')
		data->pipe_stop = 1;
	return (count);
}

t_cmd	**ft_fill_nodes(t_data *data)
{
	t_cmd	**head;
	int		cmd_n;
	char	***all_cmd;

	head = malloc(sizeof(t_cmd *));
	cmd_n = ft_count_nodes(data->cmd_trim, data);
	all_cmd = malloc(sizeof(char **) * (cmd_n + 1));
	ft_all_cmd_init(all_cmd, cmd_n, data->cmd_trim);
	all_cmd = ft_fill_all_cmd(all_cmd, cmd_n, data->cmd_trim);
	ft_node_init(head, cmd_n, all_cmd);
	ft_redirection(head);
	free (all_cmd);
	return (head);
}
