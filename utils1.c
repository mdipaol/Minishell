/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:31:34 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/17 15:50:27 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_counter(char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == c)
			n++;
		i++;
	}
	return (n);
}

int	ft_strlen_var(char *s, char *check)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (check[j])
		{
			if (s[i] == check[j])
				return (count);
			j++;
		}
		count++;
		i++;
	}
	return (count);
}
