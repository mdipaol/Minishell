/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:08:28 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/30 18:20:25 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wcounter_help2(int flag, int count)
{
	if (flag == 1)
	{
		count++;
		return (count);
	}
	return (count);
}

int	ft_wcounter_help(char **s, int i, int flag, int count)
{
	int	j;

	j = 0;
	while (s[i][j])
	{
		if (s[i][j] == '\"' || s[i][j] == '\'')
		{
			j = quote_skipper(s[i], j) - 1;
			count = ft_wcounter_help2(flag, count);
			flag = 0;
		}
		else if (s[i][j] != '|' && s[i][j] != '>' && \
		s[i][j] != '<' && flag == 1)
		{
			count++;
			flag = 0;
		}
		else if (s[i][j] == '|' || s[i][j] == '>' || s[i][j] == '<')
		{
			count++;
			flag = 1;
		}
		j++;
	}
	return (count);
}
