/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:14:33 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/21 15:52:49 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill_var(char *var, char *s, char *check)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(check, s[i]))
			break ;
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*ft_final_fill(char *original, char *new, int dollar, char *var)
{
	int	i;
	int	k;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	k = 0;
	flag = 0;
	while (original[i])
	{
		if (original[i] != '$' || flag)
			new[j++] = original[i++];
		if (i == dollar)
		{
			while (var[k])
				new[j++] = var[k++];
			i += ft_strlen_var(original + i + 1, "|\"\'$?>< ") + 1;
			flag = 1;
		}
	}
	return (new);
}

int	ft_create_str_var(t_data *data, int i, int j)
{
	char	*var;
	char	*s;

	var = malloc(sizeof(char) * \
	ft_strlen_var(data->cmd_trim[i] + j + 1, "|\"\'$?>< ") + 1);
	var = ft_fill_var(var, data->cmd_trim[i] + j + 1, "|\"\'$?>< ");
	var = getenv(var);
	if (!var)
	{
		var = malloc(1);
		var[0] = '\0';
	}
	s = malloc(sizeof(char) * ft_strlen(var) + ft_strlen(data->cmd_trim[i]) - \
	ft_strlen_var(data->cmd_trim[i] + j + 1, "|\"\'$?>< "));
	data->cmd_trim[i] = ft_final_fill(data->cmd_trim[i], s, j, var);
/* 	j += ft_strlen_var(data->cmd_trim[i] + j + 1, "|\"\'$?>< ") + 1; */
	j += ft_strlen(var) - 1;
	return (j);
}

char	**ft_expand(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->cmd_trim[i])
	{
		j = 0;
		while (data->cmd_trim[i][j])
		{
			if (data->cmd_trim[i][j] == '\'')
				j = quote_skipper(data->cmd_trim[i], j);
			if (data->cmd_trim[i][j] == '$')
				j = ft_create_str_var(data, i, j);
			j++;
		}
		i++;
	}
	return (data->cmd_trim);
}
