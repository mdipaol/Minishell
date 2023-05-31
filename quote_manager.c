/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:38:22 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/31 16:02:14 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wcounter_helper(char c, int *flag, int count)
{
	if (c != '|' && c != '>' && c != '<' && *flag == 1)
	{
		count++;
		*flag = 0;
	}
	else if (c == '|' || c == '>' || c == '<')
	{
		count++;
		*flag = 1;
	}
	return (count);
}

int	ft_check_quote(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i++];
			while (s[i] != c && s[i])
				i++;
			if (!s[i])
			{
				ft_error("Minishem: Error: unmatched quotes\n", 1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	quote_skipper(char *s, int start)
{
	char	c;

	c = s[start];
	if (s[start])
		start++;
	while (s[start] && s[start] != c)
		start++;
	start++;
	return (start);
}

char	*quote_inserter(char *s, int start)
{
	char	c;
	int		i;
	int		startcpy;
	char	*newword;

	c = s[start];
	i = 1;
	startcpy = start + 1;
	start++;
	while (s[start] != c)
	{
		i++;
		start++;
	}
	newword = malloc (sizeof(char) * i + 2);
	newword[0] = c;
	i = 1;
	while (s[startcpy] != c)
		newword[i++] = s[startcpy++];
	newword[i++] = c;
	newword[i] = '\0';
	return (newword);
}
