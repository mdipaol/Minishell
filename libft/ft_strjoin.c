/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:10:20 by mdi-paol          #+#    #+#             */
/*   Updated: 2022/10/17 19:21:47 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strcat(char *s1, char *s2, char *newstr, int i)
{
	int	x;
	int	y;
	int	j;

	x = 0;
	y = 0;
	j = ft_strlen(s2);
	while (y < i)
	{
		newstr[y] = s1[y];
		y++;
	}
	while (x < j)
	{
		newstr[y] = s2[x];
		x++;
		y++;
	}
	newstr[y] = '\0';
	return (newstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*newstr;

	i = ft_strlen(s1);
	newstr = (char *)malloc(sizeof (char) * (i + ft_strlen(s2) + 1));
	if (newstr == 0)
		return (0);
	return (ft_strcat((char *)s1, (char *)s2, newstr, i));
}
