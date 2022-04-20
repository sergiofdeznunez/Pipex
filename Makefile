CC = gcc

CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address

SRCS = pipex.c aux.c

OBJS = ${SRCS:.c=.o}

NAME = pipex

LIBFT_PATH = Libft-Mia-/

LIBFT = -L$(LIBFT_PATH) $(LIBFT_PATH)libft.a

$(NAME) :	libft $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all:	$(NAME)

libft:
		make -C $(LIBFT_PATH)

clean:
		make clean -sC $(LIBFT_PATH)
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

test:
		bash test.sh

clean_test:
		rm -rf tt_*

.PHONY = all clean fclean re