/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:03:49 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/22 17:31:37 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stddef.h>

char	*ft_fill(char *str, long int n, int i)
{
	str[i] = '\0';
	i = i - 1;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		n = n * (-1);
		str[0] = '-';
	}
	while (n != 0)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (str);
}

int	counter(long int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i = i + 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		i;
	char		*str;
	long int	a;

	a = n;
	i = counter(a);
	str = (char *)malloc(sizeof (char) * (i + 1));
	return (ft_fill(str, a, i));
}
