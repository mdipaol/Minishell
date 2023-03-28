/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:38:36 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/03/28 19:02:56 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_counter(char const *s, char c, int i, int flag)
{
	int		count;
	char	q;

	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			q = s[i];
			i++;
			count++;
			while (s[i] != q)
				i++;
			flag = 0;
		}
		if (s[i] != c && flag == 0 && s[i] != '\"' && s[i] != '\'')
		{
			count++;
			flag = 1;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static char	*word_creator(char const *s, char c, int start)
{
	char	*newword;
	int		i;
	int		startcpy;

	i = 0;
	startcpy = start;
	while (s[start] != c && s[start] != '\0' && s[start] != '\"' \
	&& s[start] != '\'')
	{
		i++;
		start++;
	}
	newword = malloc (sizeof(char) * i + 1);
	i = 0;
	if (!newword)
		return (NULL);
	while (s[startcpy] != c && s[startcpy] != '\0' && s[startcpy] != '\"' \
	&& s[startcpy] != '\'' )
	{
		newword[i] = s[startcpy];
		i++;
		startcpy++;
	}
	newword[i] = '\0';
	return (newword);
}

char	**ft_cmdtrim_helper(char *s, int i, int b, char **final)
{
	int	flag;

	flag = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			final[b] = quote_inserter(s, i);
			b++;
			i = quote_skipper(s, i);
			flag = 0;
		}
		if (s[i] != ' ' && flag == 0 && s[i])
		{
			final[b] = word_creator(s, ' ', i);
			b++;
			flag = 1;
		}
		if (s[i] == ' ')
			flag = 0;
		i++;
	}
	final[b] = NULL;
	return (final);
}

char	**ft_cmdtrim(char *s, char c)
{
	char	**final;
	int		i;
	int		b;

	b = 0;
	i = 0;
	final = malloc(sizeof(char *) * (word_counter(s, c, i, 0) + 1));
	final = ft_cmdtrim_helper(s, i, b, final);
	return (final);
}

void	ft_split_all(t_data *data, char *s)
{
	if (!ft_check_quote(s))
	{
		data->cmd_trim = ft_cmdtrim(s, ' ');
		ft_cmdsubsplit(data->cmd_trim);
		//data->expand = ft_expand(data);
	}
	else
		data->split_error = 1;
	//printf("%s", s);
/* 	for(int i = 0; data->cmd_trim[i]; i++)
		printf("%s\n", data->cmd_trim[i]); */
}
