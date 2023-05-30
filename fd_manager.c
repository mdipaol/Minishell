/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:11:16 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/30 16:32:51 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	ft_heredoc(t_cmd *tmp, char *path)
{
	char	*std_in;
	//int		i;
	int		flag;

	g_status = 0;
	flag = 0;
	unlink("/tmp/.heredoc");
	tmp->in_fd = open("/tmp/.heredoc", O_CREAT | O_RDWR | O_APPEND, 0666);
	while (g_status != 130)
	{
		std_in = readline("> ");
		if (!std_in)
		{
			write(1, "warning: here-document delimited by end-of-file\n", 49);
			break ;
		}
		flag++;
		//i = ft_strlen(std_in);
		//std_in[i] = '\n';
		if (!ft_strncmp(path, std_in, ft_strlen(path) + 1))
			break ;
		write(tmp->in_fd, std_in, ft_strlen(std_in));
		write(tmp->in_fd, "\n", 1);
	}
	close (tmp->in_fd);
	tmp->in_fd = open("/tmp/.heredoc", O_RDONLY);
	if (g_status == 130)
	{
		close (tmp->in_fd);
		tmp->in_fd = -1;
	}
}

char	*ft_obtain_path(char **full_cmd, int flag)
{
	if (flag == 0)
		return (full_cmd[2]);
	if (flag == 1)
		return (full_cmd[1]);
	if (flag == 2)
		return (full_cmd[2]);
	if (flag == 3)
		return (full_cmd[1]);
	return (0);
}

void	ft_obtain_fd(t_cmd *tmp, char *path, int flag)
{
	if ((flag == 0 || flag == 1) && tmp->in_fd > 2)
		close (tmp->in_fd);
	else if ((flag == 2 || flag == 3) && tmp->out_fd > 2)
		close (tmp->out_fd);
	if (!path)
		ft_error("Minishem: syntax error near unexpected token `newline'\n", 2);
	else if (access(path, F_OK) == -1 && flag == 1)
		ft_error("Minishem: No such file or directory\n", 1);
	else if (flag == 1 && access(path, R_OK) == -1)
		ft_error("Minishem: Permission denied\n", 1);
	else if (flag > 1 && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		ft_error("Minishem: Permission denied\n", 1);
	if (flag == 0 && path)
		ft_heredoc(tmp, path);
	if (flag == 1 && path)
		tmp->in_fd = open(path, O_RDONLY, 0666);
	else if (flag == 2 && path)
		tmp->out_fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flag == 3 && path)
		tmp->out_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
}
