/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:14:33 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/03/28 12:34:13 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_str_var(t_data *data)
{
	ciao come va?
}

int	ft_search_var(t_data *data)
{
	int		i;
	int		j;
	char	*var;

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
	ft_create_str_var(data);
	printf("%d", i);
}