/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trims_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:06:43 by alegreci          #+#    #+#             */
/*   Updated: 2023/06/01 20:05:57 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_extract_path(char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (ft_calloc(1, sizeof(char *)));
	tmp = envp[i] + 5;
	return (ft_split(tmp, ':'));
}

char	**ft_negative_restorer(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] < 0)
				cmd[i][j] = -cmd[i][j];
			j++;
		}
		i++;
	}
	return (cmd);
}

int	ft_quote_inverter(char **cmd, int i, int j)
{
	char	q;

	q = cmd[i][j];
	j++;
	if (cmd[i][j] == q)
	{
		j++;
		return (j);
	}
	while (cmd[i][j] && cmd[i][j] != q)
	{
		if (cmd[i][j] == '|' || cmd[i][j] == '<' || cmd[i][j] == '>')
			cmd[i][j] = -cmd[i][j];
		j++;
	}
	return (j);
}

char	**ft_safe_quotes(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\"' || cmd[i][j] == '\'')
				j = ft_quote_inverter(cmd, i, j);
			if (cmd[i][j])
				j++;
		}
		i++;
	}
	return (cmd);
}
