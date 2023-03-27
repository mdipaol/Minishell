/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:38:22 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/03/27 19:03:38 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote(char *s)
{
	int	i;
	int	count_s;
	int	count_db;

	count_db = 0;
	count_s = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			count_db++;
		if (s[i] == '\'')
			count_s++;
		i++;
	}
	if (count_db % 2 != 0 || count_s % 2 != 0 )
	{
		write(1, "Error: unmatched quotes\n", 24);
		return(1);
	}
	else
		return(0);
}

int	quote_skipper(char *s, int start)
{
	char	c;

	c = s[start];
	start++;
	while (s[start] != c)
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
