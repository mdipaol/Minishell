/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:31:34 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/30 18:09:22 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	ft_numstr(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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

void	ft_error(char *str, int error)
{
	g_status = error;

	if (str)
		write(2, str, ft_strlen(str));
}
