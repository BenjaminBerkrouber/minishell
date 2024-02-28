NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I.
SRC_DIR = srcs/
SRC = 	srcs/main.c srcs/utils.c \
		srcs/parsing/parsing.c srcs/parsing/tocken.c srcs/parsing/export.c srcs/parsing/quote.c \
		srcs/ast/ast.c \
		srcs/ast/utils_ast.c srcs/ast/utils_redirection.c \
		srcs/exec/exec.c srcs/exec/path.c srcs/exec/here_doc.c
		# srcs/builtins/ft_pwd.c srcs/builtins/ft_env.c srcs/builtins/ft_unset.c srcs/builtins/ft_exit.c srcs/builtins/ft_cd.c 
SRC_TEST =	unit-test/main.c \
			srcs/utils.c \
			srcs/parsing/parsing.c srcs/parsing/tocken.c srcs/parsing/export.c srcs/parsing/quote.c \
			srcs/ast.c
OBJ = $(SRC:.c=.o)
OBJ_TEST = $(SRC_TEST:.c=.o)
LIBFT_DIR = srcs/libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I includes/ -I $(LIBFT_DIR)
INCLUDES_TEST = -I test/

all: $(NAME)

bonus : $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_BONUS) $(LIBFT) -o $(NAME)

test : $(OBJ_TEST) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(INCLUDES_TEST) $(OBJ_TEST) $(LIBFT) -o test

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
