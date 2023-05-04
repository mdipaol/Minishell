/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:34:45 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/04 19:00:41 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_cleaner_helper(char **full_cmd, char **new, int i, int size)
{
	int	j;

	j = 0;
	while (i <= size)
	{
		new[j] = full_cmd[i];
		i++;
		j++;
	}
}

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
		E LO RITORNA, SE ARRIVA FLAG = 0 HEREDOC.
	*/
}

char	**ft_cmd_cleaner(char **full_cmd)
{
	int		i;
	int		j;
	int		size;
	char	**new;

	j = 0;
	i = 0;
	size = ft_cmd_clean_counter(full_cmd, i, j);
	new = malloc(sizeof(char *) * (size + 1));
	new[size] = NULL;
	size = 0;
	while (full_cmd[size])
		size++;
	size--;
	if (full_cmd[0][0] == '<' && full_cmd[1] && full_cmd[1][0] == '<')
		i = 3;
	else if (full_cmd[0][0] == '<')
		i = 2;
	if (full_cmd[size][0] == '>' && size > 0 && full_cmd[size - 1][0] == '>')
		size -= 3;
	else if (full_cmd[size][0] == '>')
		size -= 2;
	ft_cmd_cleaner_helper(full_cmd, new, i, size);
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
		ft_fd_manager(tmp, tmp->full_cmd);
		//ciclo in fd_manager, ogni qual volta che trova un redirect mandi in ft_get_fd (GOAT), e gestiamo gli fd
		// ogni volta e in base alla flag in input closiamo gli in o out fd precedenti.
		tmp->full_cmd = ft_cmd_cleaner(tmp->full_cmd);
		tmp = tmp->next;
	}
}

