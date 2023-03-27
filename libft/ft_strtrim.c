/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:01:50 by mdi-paol          #+#    #+#             */
/*   Updated: 2022/10/17 19:23:54 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>
#include<stdlib.h>
#include"libft.h"

int	ft_control(char s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*str;

	start = 0;
	i = 0;
	while (s1[start] != '\0' && ft_control(s1[start], set) == 1)
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_control(s1[end - 1], set) == 1)
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (str == 0)
		return (0);
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
