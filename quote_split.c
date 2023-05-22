/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:50:44 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/05/22 19:03:55 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_remover(char *s)
{
	char	*removed;
	int		i;
	int		q;
	char	c;

	removed = malloc(sizeof(char) * (ft_strlen(s) - 1));
	i = 0;
	q = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i++];
			while (s[i] != c)
				removed[q++] = s[i++];
			i++;
		}
		else
			removed[q++] = s[i++];
	}
	removed[q] = '\0';
	free(s);
	return (removed);
}

char	**ft_quote_split(char **s)
{
	char	**final;
	int		i;

	i = 0;
	while (s[i])
		i++;
	final = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (s[i])
	{
		if (!ft_strchr(s[i], '\"') && !ft_strchr(s[i], '\''))
			final[i] = s[i];
		else
			final[i] = quote_remover(s[i]);
		i++;
	}
	final[i] = NULL;
	free(s);
	return (final);
}
