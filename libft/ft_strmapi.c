/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:36:24 by mdi-paol          #+#    #+#             */
/*   Updated: 2022/10/17 19:18:57 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*c;

	i = 0;
	c = (char *)malloc(sizeof (char) * (ft_strlen(s) + 1));
	if (c == 0)
		return (0);
	while (s[i] != 0)
	{
		c[i] = (*f)(i, s[i]);
		i++;
	}
	c[i] = '\0';
	return (c);
}
