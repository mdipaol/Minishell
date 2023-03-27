/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:14:52 by mdi-paol          #+#    #+#             */
/*   Updated: 2022/10/17 19:19:30 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*substr;

	i = 0;
	j = 0;
	substr = (char *)malloc(sizeof (char) * (len + 1));
	if (substr == 0)
		return (0);
	while (s[i] != '\0' && i < start)
	{
		i++;
	}
	while (j < len && s[i] != '\0')
	{
		substr[j] = s[i];
		j++;
		i++;
	}
	substr[j] = '\0';
	return (substr);
}
