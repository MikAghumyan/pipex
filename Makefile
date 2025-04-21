CC=cc
CFLAGS=-Wall -Wextra -Werror

UTILS_SRC=	utils/handlers.c \
			utils/parsers.c \
			utils/fork_controllers.c \
			utils/pipe_controllers.c \
			utils/utils.c \

GNL_SRC=	get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c

SRCS= main.c $(UTILS_SRC)

OBJS= $(SRCS:.c=.o)
OBJS_GNL= $(GNL_SRC:.c=.o)

NAME=pipex
LIBFT=libft/libft.a
LIBFT_DIR=libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(OBJS_GNL)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(OBJS_GNL)

$(LIBFT):
	$(MAKE) complete -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(OBJS_GNL)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
