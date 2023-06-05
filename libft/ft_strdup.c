/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:08:44 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/06/05 15:20:49 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*a;

	a = (char *)s;
	len = ft_strlen(s) + 1;
	if (len == 1)
		return (0);
	a = malloc(len);
	if (a == 0)
		return (0);
	ft_memcpy (a, s, len);
	return (a);
}
