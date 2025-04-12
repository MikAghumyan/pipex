CC=cc
CFLAGS=-Wall -Wextra 

UTILS_SRC=	utils/handlers.c \
			utils/parsers.c \
			utils/controllers.c \

SRCS= main.c $(UTILS_SRC)
OBJS= $(SRCS:.c=.o)

NAME=pipex
LIBFT=libft/libft.a
LIBFT_DIR=libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
