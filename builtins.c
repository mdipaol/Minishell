/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:06:20 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/16 12:17:29 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *full_cmd)
{
	if (ft_strncmp(full_cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

