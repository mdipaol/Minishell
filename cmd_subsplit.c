/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_subsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:36:04 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/04/03 11:34:37 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr_quote(const char *s, int c)
{
	int		i;
	char	*a;

	a = (char *)s;
	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] == '\'' || a[i] == '\"')
			i = quote_skipper((char *)s, i);
		if (a[i] == c)
			return (&a[i]);
		i++;
	}
	if (c == '\0')
		return (&a[i]);
	return (NULL);
}

int	special_char_putter(char **final, int i, int j, char *s)
{
	final[j] = malloc(sizeof(char) * 2);
	final[j][0] = s[i];
	final[j][1] = '\0';
	i++;
	return (i);
}

int	ft_string_splitter(char **final, int j, char *s, int i)
{
	char	*tmp;
	int		start;

	while (s[i])
	{
		start = i;
		while (s[i] && s[i] != '|' && s[i] != '>' && s[i] != '<')
			i++;
		if (i - start != 0)
		{
			tmp = malloc(sizeof(char) * (i - start) + 1);
			tmp[i - start] = '\0';
			i = start;
			start = 0;
			while (s[i] && s[i] != '|' && s[i] != '>' && s[i] != '<')
				tmp[start++] = s[i++];
			final[j++] = tmp;
		}
		while (s[i] == '|' || s[i] == '>' || s[i] == '<')
			i = special_char_putter(final, i, j++, s);
	}
	free(s);
	return (j);
}

int	ft_wcounter(char **s, int i, int j)
{
	int	count;

	count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == '\"' || s[i][j] == '\'')
				j = quote_skipper(s[i], j);
			if (s[i][j] == '|' || s[i][j] == '>' || s[i][j] == '<')
				count++;
			j++;
		}
		i++;
	}
	count += i;
	return (count);
}

char	**ft_cmdsubsplit(char **s)
{
	int		i;
	int		j;
	char	**final;

	i = 0;
	j = 0;
	final = malloc(sizeof(char *) * ft_wcounter(s, i, j) + 1);
	while (s[i])
	{
		if (!ft_strchr_quote(s[i], '|')
			&& !ft_strchr_quote(s[i], '>') && !ft_strchr_quote(s[i], '<'))
		{
			final[j] = s[i];
			j++;
		}
		else
			j = ft_string_splitter(final, j, s[i], 0);
		i++;
	}
	final[j] = NULL;
	return (final);
}
