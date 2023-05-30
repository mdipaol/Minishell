# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 13:45:50 by mdi-paol          #+#    #+#              #
#    Updated: 2023/05/30 18:09:10 by mdi-paol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a
GNL = Get_Next_Line/get_next_line.c Get_Next_Line/get_next_line_utils.c
SRC = main.c cmd_trim.c quote_manager.c expand_var.c utils1.c cmd_subsplit.c trims_helpers.c quote_split.c builtins3.c fill_nodes.c path_finder.c nodes_helper.c fd_manager.c execution.c builtins.c builtins2.c signal.c free.c utils2.c
FLAGS = -Wall -Werror -Wextra -g

all : $(NAME)

$(NAME) : lf ps

lf:
	@make -sC libft
	@make bonus -sC libft

ps:
			gcc $(FLAGS) $(SRC) $(LIBFT) $(GNL) -lreadline -g -o $(NAME)
			@echo "\033[1;32m✅ Compiled ✅\033[0m"

clean :		libclean
			rm -rf
			@echo "\033[1;34m☑️  Clean ☑️\033[0m"

libclean :
	@make clean -sC libft

fclean :	clean libfclean
			rm -rf $(NAME) $(NAME_BONUS)
			@echo "\033[1;34m☑️  Clean ☑️\033[0m"

libfclean :
			@make fclean -sC libft

re : fclean all

.SILENT:
