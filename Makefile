# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 17:44:47 by kprigent          #+#    #+#              #
#    Updated: 2024/03/26 10:38:35 by kprigent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini_shell

SRCS = src_exec/start_exec.c \
		src_exec/create_pipe.c \
		src_exec/utils.c \
		src_exec/utils_path.c \
		src_exec/find_verif_cmd.c \
		src_exec/signal.c \
		src_parsing/main.c \
		src_parsing/utils.c \
		src_parsing/init.c \
		src_parsing/count_blocks.c \
		src_parsing/create_list.c \
		src_parsing/lexer.c \
		src_parsing/first_errors.c \
		src_parsing/free_function.c \
		src_parsing/exits.c \
		src_parsing/to_nodes.c \
		src_parsing/print_it.c \
		libft/ft_strlen.c \
		libft/ft_substr.c \
		libft/ft_strjoin.c \
		libft/ft_strncmp.c \
		libft/ft_split.c \
		libft/ft_putstr_fd.c \
		libft/ft_memcpy.c \
		bultins/bultins.c \
		bultins/cd.c \
		bultins/echo.c \
		bultins/unset.c \
		bultins/env.c \
		bultins/pwd.c \
		bultins/export.c
		
		
		
OBJTS = $(SRCS:.c=.o)

HEADER = -I includes
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

$(NAME): $(OBJTS)
	cc -o $(NAME) $(OBJTS) -lreadline -lhistory 

RM	= rm -f

all:	${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${OBJTS}
	
fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
