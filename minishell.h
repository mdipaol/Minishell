/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:35 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/12 16:35:01 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "Get_Next_Line/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char			**full_cmd;
	char			*full_path;
	int				in_fd;
	int				out_fd;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_data
{
	t_cmd	**cmds;
	int		run;
	int		count_word;
	int		split_error;
	char	**cmd_trim;
	char	**expand;
}	t_data;

void	ft_redirection(t_cmd **head);
t_cmd	**ft_fill_nodes(t_data *data);
void	ft_split_all(t_data *data, char *s);
int		quote_skipper(char *s, int start);
char	*quote_inserter(char *s, int start);
int		ft_check_quote(char *s);
char	**ft_expand(t_data *data);
int		ft_check_expand(char *s, char *check);
int		ft_strlen_var(char *s, char *check);
char	**ft_cmdsubsplit(char **s);
char	**ft_quote_split(char **s);
int		ft_get_fd(t_cmd *tmp, char **full_cmd, int flag);
char	*ft_obtain_path(char **full_cmd, int flag);
void	ft_obtain_fd(t_cmd *tmp, char *path, int flag);
char	*ft_full_path_finder(char **full_cmd, char **path);
void	ft_executor(t_data	*data);

#endif
