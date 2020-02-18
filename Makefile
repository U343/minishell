# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wanton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/23 13:15:24 by wanton            #+#    #+#              #
#    Updated: 2020/01/30 13:11:31 by wanton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./src/
LIB_PATH = ./lib/
OBJ_PATH = ./obj/
INC_PATH = ./includes/ $(LIB_PATH)

SRC_FILES = cd_assist.c check_bin_assist.c scan_env.c change_env.c check_bin.c echo_script.c env_assist.c env_function.c cd_script.c pwd_script.c main.c list_functions.c run_command.c
OBJ_FILES = $(SRC_FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror

SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))
INC = $(addprefix -I, $(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIB_PATH)
		gcc $(FLAGS) $(OBJ)  $(INC) -L $(LIB_PATH) -lft -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		mkdir -p $(OBJ_PATH)
		gcc $(FLAGS)  $(INC) -c $< -o $@

clean:
		make -C $(LIB_PATH)/ clean
		/bin/rm -rf $(OBJ_PATH)

fclean: clean
		make -C $(LIB_PATH)/ fclean
		/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME)
