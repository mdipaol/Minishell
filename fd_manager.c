/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:11:16 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/15 16:00:36 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	ft_get_str_heredoc(char *str, int flag)
{
	int		fd;
	char	*heredoc;
	int		i;

	i = 0;
	fd = open("/tmp/.heredoc", O_RDONLY);
	while (i < flag)
	{
		heredoc = get_next_line(fd);
		i++;
	}
	if (ft_strncmp(str, heredoc, ft_strlen(str)) == 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
} */

void	ft_heredoc(t_cmd *tmp, char *path)
{
	char	*std_in;
	int		i;
	int		flag;

	flag = 0;
	unlink("/tmp/.heredoc");
	tmp->in_fd = open("/tmp/.heredoc", O_CREAT | O_RDWR | O_APPEND, 0666);
	while (1)
	{
		std_in = readline("> ");
		flag++;
		i = ft_strlen(std_in);
		std_in[i] = '\n';
		if(!ft_strncmp(path, std_in, ft_strlen(path)))
			break ;
		write(tmp->in_fd, std_in, ft_strlen(std_in));
	}
	close (tmp->in_fd);
	tmp->in_fd = open("/tmp/.heredoc", O_RDONLY);
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
	if (access(path, F_OK) == -1 && flag == 1)
		write(2, "error\n", 6);
	else if (flag == 1 && access(path, R_OK) == -1)
		write(2, "error\n", 6);
	else if (flag > 1 && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		write(2, "error\n", 6);
	if (flag == 0)
		ft_heredoc(tmp, path);
	if (flag == 1)
		tmp->in_fd = open(path, O_RDONLY, 0666);
	else if (flag == 2)
		tmp->out_fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flag == 3)
		tmp->out_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
}
