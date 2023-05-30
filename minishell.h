/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:35 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/30 18:06:32 by mdi-paol         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>

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
	char	**envp;
	int		pipe_stop;
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
void	ft_get_fd(t_cmd *tmp, char **full_cmd, int flag);
char	*ft_obtain_path(char **full_cmd, int flag);
void	ft_obtain_fd(t_cmd *tmp, char *path, int flag);
char	*ft_full_path_finder(char **full_cmd, char **path);
void	ft_execution_manager(t_data	*data);
int		ft_is_builtin(char *tmp);
void	ft_builtin(t_cmd *tmp, char ***envp, t_data *data);
int		ft_char_counter(char *s, char c);
void	ft_cd(char **full_cmd, char **envp);
void	ft_export(char **full_cmd, char ***envp);
void	ft_unset(char **cmd, char ***envp);
void	ft_handler_sigint(int sig);
void	ft_exit(char **cmd, t_data *data);
void	ft_error(char *str, int error);
int		ft_numstr(char *str);
void	ft_free_all(t_data *data);
t_cmd	*ft_free_nodes(t_cmd *cmd);
void	ft_free_redirect(char **full_cmd);
char	**ft_negative_restorer(char **cmd);
char	**ft_safe_quotes(char **cmd);
int		ft_wcounter_help(char **s, int i, int flag, int count);

#endif
