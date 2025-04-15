CC=cc
CFLAGS=-Wall -Wextra 

UTILS_SRC=	utils/handlers.c \
			utils/parsers.c \
			utils/controllers.c \

BONUS_SRC=  bonus/controllers_bonus.c \
			bonus/handlers_bonus.c \

GNL_SRC=	get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c

SRCS= main.c $(UTILS_SRC)
SRCS_BONUS= main_bonus.c $(UTILS_SRC) $(BONUS_SRC)

OBJS= $(SRCS:.c=.o)
OBJS_BONUS= $(SRCS_BONUS:.c=.o)
OBJS_GNL= $(GNL_SRC:.c=.o)

NAME=pipex
LIBFT=libft/libft.a
LIBFT_DIR=libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

bonus: $(OBJS_BONUS) $(LIBFT) $(OBJS_GNL)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BONUS) $(LIBFT) $(OBJS_GNL)

$(LIBFT):
	$(MAKE) complete -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_GNL)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
