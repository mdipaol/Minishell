/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:45:53 by mdi-paol          #+#    #+#             */
/*   Updated: 2022/10/19 17:00:19 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == 0)
	{
		*lst = new;
		new->next = 0;
	}
	else
	{
		while (tmp->next != 0)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->next = 0;
	}
}
