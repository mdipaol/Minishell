/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:16:21 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/03/24 17:20:01 by mdi-paol         ###   ########.fr       */
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
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*s;

	s = NULL;
	ft_initialize(&data);
	while (data.run)
	{
		s = readline("\033[0;96mminishem: \033[0m");
		add_history(s);

	}
}

