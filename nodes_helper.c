/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:34:45 by alegreci          #+#    #+#             */
/*   Updated: 2023/04/28 12:43:59 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_fd(char **full_cmd, int flag)
{
	if (full_cmd)
		return 0;
	else
		return flag;
	/* DA IMPLEMENTARE :
		IN BASE AL TIPO DI FLAG CHE E' ARRIVATA APRE IL FILE DESCRIPTOR
		E LO RITORNA, SE ARRIVA FLAG = 2 HEREDOC.
	*/
}

char	**ft_cmd_cleaner(char **full_cmd)
{
	if (full_cmd)
		return full_cmd;
	else
		return NULL;
	/* DA IMPLEMENTARE :
		CERCA LE REDIRECTION NEL COMANDO E SE NE TROVA RIALLOCA E LE TOGLIE,
		LASCIANDO SOLO IL COMANDO DA ESEGUIRE CON EVENTUALI ARGOMENTI
	*/
}

void	ft_redirection(t_cmd **head)
{
	t_cmd *tmp;
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
	}
}

