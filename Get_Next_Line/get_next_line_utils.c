/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:51:02 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/12 15:51:33 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_ssstrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_sstrcat(char *s1, char *s2, char *newstr, int i)
{
	int	x;
	int	y;
	int	j;

	x = 0;
	y = 0;
	j = ft_ssstrlen(s2);
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
	free ((char *)s1);
	return (newstr);
}

char	*ft_sstrjoin(const char *s1, const char *s2)
{
	int		i;
	char	*newstr;

	i = ft_ssstrlen((char *)s1);
	newstr = (char *)malloc(sizeof (char) * (i + ft_ssstrlen((char *)s2) + 1));
	if (newstr == 0)
		return (0);
	return (ft_sstrcat((char *)s1, (char *)s2, newstr, i));
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*a;

	i = 0;
	a = s;
	while (i < n)
	{
		a[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*a;

	a = (void *)malloc(nmemb * size);
	if (a == 0)
		return (0);
	ft_bzero(a, nmemb * size);
	return (a);
}
