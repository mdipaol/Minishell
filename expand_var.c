/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:14:33 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/03/31 12:36:31 by mdi-paol         ###   ########.fr       */
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

void	ft_expand_arg(t_data *data, char *s, int index)
{
	int	i;
	int	j;
	int	x;
	int k;
	char *arg;

	arg = ft_strdup(getenv(s));
	if (arg == NULL)
	i = 0;
	x = 0;
	k = 0;
	data->expand = malloc(sizeof(char *) * data->count_word + 1);
	while (data->cmd_trim[i])
	{
		j = 0;
		if (index == i && arg != NULL)
		{
			data->expand[i] = malloc(sizeof(char) * ft_strlen(data->cmd_trim[i]) + ft_strlen(arg) - ft_strlen(s) + 1);
			while(data->cmd_trim[i][j])
			{
				if (data->cmd_trim[i][j] != '$')
				{
					data->expand[i][j] = data->cmd_trim[i][k];
					j++;
					k++;
				}
				else
				{
					while(arg[x])
					{
						data->expand[i][j] = arg[x];
						x++;
						j++;
					}
					k += ft_strlen(s) + 1;
				}
			}
		}
		else
			data->expand[i] = data->cmd_trim[i];
		i++;
	}
}

void	ft_create_str_var(t_data *data, int i)
{
	int	j;
	char *s;
	int	x;

	j = 0;
	x = 0;
	s = malloc(sizeof(char) * ft_strlen_var(data->cmd_trim[i], "|\"\'$?>< ") + 1);
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
	s[x] = '\0';
	ft_expand_arg(data, s, i);
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
