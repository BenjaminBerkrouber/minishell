NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I.
SRC_DIR = srcs/
SRC = 	srcs/main.c srcs/utils.c srcs/tocken.c srcs/three.c srcs/ast.c \
		srcs/export.c srcs/quote.c
SRC_BONUS = 
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
LIBFT_DIR = srcs/libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I includes/ -I $(LIBFT_DIR)

all: $(NAME)

bonus : $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_BONUS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME) a.out
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
