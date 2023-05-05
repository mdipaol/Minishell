/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:11:16 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/05 17:25:37 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_obtain_path(char **full_cmd, int flag)
{
	if (flag == 0)
		return(full_cmd[2]);
	if (flag == 1)
		return(full_cmd[1]);
	if (flag == 2)
		return(full_cmd[2]);
	if (flag == 3)
		return(full_cmd[1]);
	return (0);
}

void	ft_obtain_fd(t_cmd *tmp, char *path, int flag)
{
	if ((flag == 0 || flag == 1) && tmp->in_fd > 2)
		close (tmp->in_fd);
	else if ((flag == 2 || flag == 3) && tmp->out_fd > 2)
		close (tmp->out_fd);
	if (access(path, F_OK) == -1 && flag == 1)
		write(2, "error\n", 6);
	else if (flag == 1 && access(path, R_OK) == -1)
		write(2, "error\n", 6);
	else if (flag > 1 && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		write(2, "error\n", 6);
/* 	if (flag == 0)
		ft_heredoc(); */
	if (flag == 1)
		tmp->in_fd = open(path, O_RDONLY, 0666);
	else if (flag == 2)
		tmp->out_fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flag == 3)
		tmp->out_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
}
