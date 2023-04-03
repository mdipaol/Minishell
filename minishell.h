/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <alegreci>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:35 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/04/03 14:55:57 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	int		run;
	int		count_word;
	int		split_error;
	char	**cmd_trim;
	char	**expand;
}	t_data;

void	ft_split_all(t_data *data, char *s);
int		quote_skipper(char *s, int start);
char	*quote_inserter(char *s, int start);
int		ft_check_quote(char *s);
char	**ft_expand(t_data *data);
int		ft_check_expand(char *s, char *check);
int		ft_strlen_var(char *s, char *check);
char	**ft_cmdsubsplit(char **s);
char	**ft_quote_split(char **s);

#endif
