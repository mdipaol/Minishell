/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:35 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/03/28 10:23:37 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	int	run;
	int split_error;
	char **cmd_trim;
	char **expand;
} t_data;

void ft_split_all(t_data *data, char *s);
int	quote_skipper(char *s, int start);
char	*quote_inserter(char *s, int start);
int	ft_check_quote(char *s);
char **ft_expand(t_data *data);
