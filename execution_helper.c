/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:54:13 by alegreci          #+#    #+#             */
/*   Updated: 2023/06/05 15:01:48 by alegreci         ###   ########.fr       */
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

void	ft_child(t_data *data, t_cmd *tmp, int j_special, char ***envp)
{
	if (!tmp->full_path || ft_is_builtin(tmp->full_cmd[j_special]))
	{
		ft_free_envp(data->envp);
		ft_free_all(data);
		exit(g_status);
	}
	execve(tmp->full_path, tmp->full_cmd + j_special, *envp);
	exit(g_status);
}

void	ft_parent(int *std, t_cmd *tmp, int pid)
{
	int	child_status;

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
