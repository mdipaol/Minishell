# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alegreci <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 13:45:50 by mdi-paol          #+#    #+#              #
#    Updated: 2023/04/28 11:34:26 by alegreci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a
GNL = Get_Next_Line/get_next_line.c Get_Next_Line/get_next_line_utils.c
SRC = main.c cmd_trim.c quote_manager.c expand_var.c utils1.c cmd_subsplit.c quote_split.c fill_nodes.c nodes_helper.c
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
