/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:10:20 by mdi-paol          #+#    #+#             */
/*   Updated: 2022/10/17 17:02:05 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*a;
	char		*b;

	i = 0;
	a = src;
	b = dest;
	while (i < n)
	{
		b[i] = a[i];
		i++;
	}
	return (dest);
}
