/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:14:33 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/26 17:59:07 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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
			i += ft_strlen_var(original + i + 1, "|\"\'$>< ") + 1;
			flag = 1;
		}
		else
			i++;
	}
	new[j] = '\0';
	free(original);
	return (new);
}

int	ft_create_str_var(t_data *data, int i, int j, int flag)
{
	char	*var;
	char	*s;

	var = malloc(sizeof(char) * \
	ft_strlen_var(data->cmd_trim[i] + j + 1, "|\"\'$>< ") + 1);
	var = ft_fill_var(var, data->cmd_trim[i] + j + 1, "|\"\'$>< ");
	var = getenv(var);
	if (data->cmd_trim[i][j + 1] == '?')
	{
		var = ft_itoa(g_status);
		flag = 1;
	}
	if (!var)
	{
		var = malloc(1);
		var[0] = '\0';
		flag = 1;
	}
	s = malloc(sizeof(char) * ft_strlen(var) + ft_strlen(data->cmd_trim[i]) - \
	ft_strlen_var(data->cmd_trim[i] + j + 1, "|\"\'$>< "));
	data->cmd_trim[i] = ft_final_fill(data->cmd_trim[i], s, j, var);
	j += ft_strlen(var) - 1;
	if (flag)
		free(var);
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
		if (data->cmd_trim[i + 1] && !ft_strncmp(data->cmd_trim[i + 1], "$", 2))
			return (data->cmd_trim);
		while (data->cmd_trim[i][j])
		{
			if (data->cmd_trim[i][j] == '\'')
				j = quote_skipper(data->cmd_trim[i], j);
			if (data->cmd_trim[i][j] == '$' && !ft_strchr("|\"\'$>< ", data->cmd_trim[i][j + 1]))
				j = ft_create_str_var(data, i, j, 0);
			j++;
		}
		i++;
	}
	return (data->cmd_trim);
}
