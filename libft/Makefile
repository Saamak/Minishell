SRC 	   = ft_strlen \
			 ft_memcpy \
			 ft_isalpha \
			 ft_isdigit \
			 ft_isalnum \
			 ft_isascii \
			 ft_isprint \
			 ft_memset \
			 ft_bzero \
			 ft_toupper \
			 ft_tolower \
			 ft_strchr \
			 ft_strrchr \
			 ft_strncmp \
			 ft_calloc \
			 ft_strdup \
			 ft_atoi \
			 ft_strnstr \
			 ft_strlcat \
			 ft_strlcpy \
			 ft_memmove \
			 ft_memcmp \
			 ft_memchr \
			 ft_putchar_fd \
			 ft_putstr_fd \
			 ft_putendl_fd \
			 ft_putnbr_fd \
			 ft_striteri \
			 ft_strmapi \
			 ft_itoa \
			 ft_strjoin \
			 ft_substr \
			 ft_strtrim \
			 ft_split \

SRCBONUS   = ft_lstnew \
			 ft_lstadd_front \
			 ft_lstsize \
			 ft_lstlast \
			 ft_lstadd_back \
			 ft_lstdelone \
			 ft_lstclear \
			 ft_lstiter \
			 ft_lstmap \

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

EXEC	= libft.a

CFILES	= $(SRC:%=%.c)

CBONUS = $(SRCBONUS:%=%.c)

OBJ	= $(SRC:=.o)

OBJBONUS = $(SRCBONUS:=.o)

NAME	= $(EXEC)

$(NAME):
	$(CC) $(CFLAGS) -c $(CFILES) -I./
	ar -rc $(EXEC) $(OBJ)

all: $(NAME)

bonus :
	$(CC) $(CFLAGS) -c $(CBONUS) -I./
	ar -rc $(EXEC) $(OBJBONUS)

clean:
	rm -f $(OBJ)
	rm -f $(OBJBONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(OBJ)

re: fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(CFILES) $(CBONUS)
	gcc -nostartfiles -shared -o libft.so $(OBJ) $(OBJBONUS)

.PHONY: all, clean, fclean, re
