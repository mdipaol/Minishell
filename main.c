/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegreci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:16:21 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/06/05 15:21:27 by alegreci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	**ft_envp_init(char **envp)
{
	int		i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_initialize(t_data *data, char **envp)
{
	/* printf("\033[0;96m███╗░░░███╗██╗███╗░░██╗██╗░░░██████╗██╗░░██╗███████╗███╗░░░███╗\n\
████╗░████║██║████╗░██║██║░░██╔════╝██║░░██║██╔════╝████╗░████║\n\
██╔████╔██║██║██╔██╗██║██║░░╚█████╗░███████║█████╗░░██╔████╔██║\n\
██║╚██╔╝██║██║██║╚████║██║░░░╚═══██╗██╔══██║██╔══╝░░██║╚██╔╝██║\n\
██║░╚═╝░██║██║██║░╚███║██║░░██████╔╝██║░░██║███████╗██║░╚═╝░██║\n\
╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░╚═════╝░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝\033[0m");
	printf("\n\n\n"); */
	data->run = 1;
	data->split_error = 0;
	data->cmd_trim = NULL;
	data->envp = ft_envp_init(envp);
	g_status = 0;
	data->free_envp = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*s;

	(void)argc;
	(void)argv;
	s = NULL;
	ft_initialize(&data, envp);
	while (data.run)
	{
		signal(SIGINT, ft_handler_sigint);
		signal(SIGQUIT, SIG_IGN);
		s = readline("\033[0;96mminishem: \033[0m");
		add_history(s);
		if (!s)
			break ;
		if (s[0] != '\0')
		{
			ft_split_all(&data, s);
			ft_execution_manager(&data);
			ft_free_all(&data);
		}
	}
	ft_free_envp(data.envp);
	write(1, "exit\n", 5);
	exit(g_status);
}
