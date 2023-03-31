/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:31:34 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/03/31 21:29:14 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_var(char *s, char *check)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			while(s[i])
			{
				j = 0;
				while(check[j])
				{
					if(s[i] == check[j])
						return(count);
					j++;
				}
				count++;
				i++;
			}
		}
		i++;
	}
	return(count);
}

int	ft_check_expand(char *s, char *check)
{
	int	i;
	int	j;

	i = 0;
	while(s[i])
	{
		j = 0;
		while (check[j])
		{
			if (s[i] == check[j])
				return(1);
			j++;
		}
		i++;
	}
	return(0);
}
