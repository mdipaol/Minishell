/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:32:07 by mdi-paol          #+#    #+#             */
/*   Updated: 2022/10/17 17:34:18 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*a;
	char		*b;

	i = 0;
	a = src;
	b = dest;
	if (a < b)
	{
		while (i < n)
		{
			b[n - i - 1] = a[n - i - 1];
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			b[i] = a[i];
			i++;
		}
	}
	return (dest);
}
