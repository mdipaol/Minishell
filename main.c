/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:16:21 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/22 11:09:11 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize(t_data *data)
{
	printf("\033[0;96m███╗░░░███╗██╗███╗░░██╗██╗░░░██████╗██╗░░██╗███████╗███╗░░░███╗\n\
████╗░████║██║████╗░██║██║░░██╔════╝██║░░██║██╔════╝████╗░████║\n\
██╔████╔██║██║██╔██╗██║██║░░╚█████╗░███████║█████╗░░██╔████╔██║\n\
██║╚██╔╝██║██║██║╚████║██║░░░╚═══██╗██╔══██║██╔══╝░░██║╚██╔╝██║\n\
██║░╚═╝░██║██║██║░╚███║██║░░██████╔╝██║░░██║███████╗██║░╚═╝░██║\n\
╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░╚═════╝░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝\033[0m");
	printf("\n\n\n");
	data->run = 1;
	data->split_error = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*s;

	(void)argc;
	(void)argv;
	data.envp = envp;
	s = NULL;
	ft_initialize(&data);
	while (data.run)
	{
		signal(SIGINT, ft_handler_sigint);
		signal(SIGQUIT, SIG_IGN);
		s = readline("\033[0;96mminishem: \033[0m");
		add_history(s);
		ft_split_all(&data, s);
		ft_execution_manager(&data);
	}
	return (0);
}

