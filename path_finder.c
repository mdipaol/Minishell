/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:57:57 by alegreci          #+#    #+#             */
/*   Updated: 2023/05/08 17:06:08 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_full_path_finder(char **full_cmd, t_cmd *tmp, char **path)
{
	if (tmp)
		return (full_cmd[0]);
	else
		return (path[0]);
}
