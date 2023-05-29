/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:33:32 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/29 17:29:23 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	ft_save_std(int *std, int flag)
{
	if (flag)
	{
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
		close(std[0]);
		close(std[1]);
	}
	else
	{
		dup2(STDIN_FILENO, std[0]);
		dup2(STDOUT_FILENO, std[1]);

	}
}

void	ft_check_redirect(t_cmd *tmp)
{
	if (tmp->in_fd != STDIN_FILENO)
	{
		dup2(tmp->in_fd, STDIN_FILENO);
		close (tmp->in_fd);
	}
	if (tmp->out_fd != STDOUT_FILENO)
	{
		dup2(tmp->out_fd, STDOUT_FILENO);
		close (tmp->out_fd);
	}
}

void	ft_pipe(t_cmd *tmp)
{
	int	fd[2];

	pipe(fd);
	if (tmp->out_fd != 1)
	{
		dup2(tmp->out_fd, fd[1]);
		close(tmp->out_fd);
	}
	if (tmp->next->in_fd != 0)
	{
		tmp->out_fd = fd[1];
		return;
	}
	tmp->out_fd = fd[1];
	tmp->next->in_fd = fd[0];
}

void	ft_exec(t_cmd *tmp, char ***envp, t_data *data)
{
	pid_t	pid;
	int		std[2];
	int		child_status;

	if (!tmp->full_cmd[0])
		return ;
	if (pipe(std) == -1)
		ft_error("Minishem: error creating pipe\n", 1);
	ft_save_std(std, 0);
	ft_check_redirect(tmp);
	if (ft_is_builtin(tmp->full_cmd[0]))
		ft_builtin(tmp, envp, data);
	pid = fork();
	if (pid < 0)
		ft_error ("Minishem: fork failed\n", 1);
	if (pid == 0)
	{
		if (!tmp->full_path || ft_is_builtin(tmp->full_cmd[0]))
			exit(g_status);
		execve(tmp->full_path, tmp->full_cmd, *envp);
		exit(g_status);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_save_std(std, 1);
	if (tmp->out_fd != 1)
		close(tmp->out_fd);
	if (tmp->in_fd != 0)
		close(tmp->in_fd);
	waitpid(pid, &child_status, 0);
	if (WIFEXITED(child_status))
		g_status = WEXITSTATUS(child_status);
}

void	ft_execution_manager(t_data	*data)
{
	t_cmd	*tmp;

	if (data->pipe_stop || g_status == 2)
		return ;
	tmp = *data->cmds;
	while (tmp)
	{
		if (tmp->in_fd >= 0 && tmp->out_fd >= 0)
		{
			if (tmp->next)
				ft_pipe(tmp);
			ft_exec(tmp, &data->envp, data);
		}
		tmp = tmp->next;
		//tmp = ft_free_nodes(tmp);
	}

}
