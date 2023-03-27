/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:58:47 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/02/09 14:55:26 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstiter(t_list *lst, void (*f)(int))
{
	t_list	*tmp;
	t_list	*d;

	tmp = lst;
	while (tmp != 0)
	{
		d = tmp;
		tmp = tmp->next;
		(*f)(d->content);
	}
}
