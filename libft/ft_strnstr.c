/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:25:04 by mdi-paol          #+#    #+#             */
/*   Updated: 2022/10/17 18:10:57 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = 0;
	a = (char *)big;
	if (little == 0)
		return (a);
	while (i < len && a[i] != '\0')
	{
		while (little[j] == a[i + j] && a[i + j] != '\0' && i + j < len)
		{
			j++;
		}	
		if (little[j] == '\0')
			return (&a[i]);
		else
			j = 0;
		i++;
	}
	return (0);
}
