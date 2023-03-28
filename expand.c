/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:14:33 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/03/28 19:19:45 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_first_c(t_data *data, char *check, int i, int j)
{
	int	x;

	x = 0;
	while (check[x])
	{
		if (data->cmd_trim[i][j] == check[x])
			return(0);
		x++;
	}
	return(1);
}

void	ft_expand_arg(t_data *data, char *s)
{
	int	i;
	int	j;
	int	x;
	char *arg;

	arg = getenv(s);
	i = 0;
	x = 0;
	printf("%s", arg);
	/* while (data->cmd_trim[i])
	{
		j = 0;
		while(data->cmd_trim[i][j])
		{
			if (data->cmd_trim[i][j] != '$')
			{
				data->expand[i][j] = data->cmd_trim[i][j];
				j++;
			}
			else
			{
				j--;
				while(arg[x])
				{
					data->expand[i][j] = arg[x];
					x++;
				}
			}
		}
		i++;
	}
	for(int u = 0; data->expand[u]; u++)
		printf("%s\n", data->expand[u]); */
}

void	ft_create_str_var(t_data *data, int i)
{
	int	j;
	char *s;
	int	x;

	j = 0;
	x = 0;
	s = malloc(sizeof(char) * ft_strlen(data->cmd_trim[i]) - i);
	while (data->cmd_trim[i][j])
	{
		if (data->cmd_trim[i][j] == '$' && data->cmd_trim[i][j + 1])
		{
			j++;
			if (!ft_check_first_c(data, "|\"\'$?>< ", i, j))
				break;
			while (ft_check_first_c(data, "|\"\'$?>< ", i, j) && data->cmd_trim[i][j])
			{
				s[x] = data->cmd_trim[i][j];
				x++;
				j++;
			}
		}
		j++;
	}
	ft_expand_arg(data, s);
}

int	ft_search_var(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->cmd_trim[i])
	{
		j = 0;
		while (data->cmd_trim[i][j])
		{
			if (data->cmd_trim[i][j] == '$' && data->cmd_trim[i][j + 1])
				return (i);
			j++;
		}
		i++;
	}
}

char	**ft_expand(t_data *data)
{
	int	i;

	i = ft_search_var(data);
	ft_create_str_var(data, i);
	//printf("%d", i);
}
