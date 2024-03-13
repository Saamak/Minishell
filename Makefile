# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 16:43:36 by ppitzini          #+#    #+#              #
#    Updated: 2024/03/13 14:53:55 by ppitzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= ./src/main \
		./src/utils \
			./src/init \
				./src/count_blocks \
					./src/create_list \
					./src/lexer \
					./src/first_errors \
					./src/free_function \
					./src/exits \
					./src/to_nodes \
					./src/print_it
CC	= cc

CFLAGS	= -Wall -Wextra -Werror -g

LDFLAGS = -lreadline -lhistory

EXEC	= Minishell

CFILES	= $(SRC:%=%.c)

OBJ	= $(SRC:=.o)

NAME = $(EXEC)

$(NAME): $(OBJ)
	${MAKE} -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) ./libft/libft.a $(LDFLAGS)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${MAKE} -C ./libft clean
	rm -f $(OBJ)

fclean: clean
	${MAKE} -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
