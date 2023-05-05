/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:38:36 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/05 15:40:22 by mdi-paol         ###   ########.fr       */
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
			i = quote_skipper(s, i) - 1;
			flag = 0;
		}
		else if (s[i] != ' ' && flag == 0 && s[i])
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

char	**ft_cmdtrim(t_data *data, char *s, char c)
{
	char	**final;
	int		i;
	int		b;

	b = 0;
	i = 0;
	data->count_word = word_counter(s, c, i, 0);
	final = malloc(sizeof(char *) * (word_counter(s, c, i, 0) + 1));
	final = ft_cmdtrim_helper(s, i, b, final);
	return (final);
}

void	ft_split_all(t_data *data, char *s)
{
	if (!ft_check_quote(s))
	{
		data->cmd_trim = ft_cmdtrim(data, s, ' ');
		if (ft_strchr(s, '$'))
			data->cmd_trim = ft_expand(data);
		data->cmd_trim = ft_cmdsubsplit(data->cmd_trim);
		data->cmd_trim = ft_quote_split(data->cmd_trim);
		data->cmds = ft_fill_nodes(data);
	}
	else
		data->split_error = 1;
/*    	for(int i = 0; data->cmd_trim[i]; i++)
		printf("%s\n", data->cmd_trim[i]); */
}
