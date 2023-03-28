/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_subsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:36:04 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/03/28 19:25:56 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!ft_strchr(s[i],'|') && !ft_strchr(s[i],'>') && !ft_strchr(s[i],'<'))
		{
			final[j] = s[i];
			j++;
		}
		else
			j = //funione che mette le stringhe;

	}

	return (final);
}
