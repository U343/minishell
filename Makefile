# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wanton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/23 13:15:24 by wanton            #+#    #+#              #
#    Updated: 2020/01/22 15:42:54 by wanton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB_PATH = lib/

SRC = main.c list_functions.c

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LIB_PATH)
		@gcc $(FLAGS) $(OBJ) -L $(LIB_PATH) -lft -o $(NAME)

./%.o: %.c
		@gcc $(FLAGS) -c $< -o $@ 

clean:
		@make -C $(LIB_PATH)/ clean
		@/bin/rm -f $(OBJ) 

fclean: clean
		@make -C $(LIB_PATH)/ fclean
		@/bin/rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re
