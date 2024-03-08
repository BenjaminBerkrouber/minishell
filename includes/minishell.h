/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:45:18 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 23:19:21 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_last_exit_status;

# include <unistd.h>
# include "../libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef enum {
    CMD,
	OPTION,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HERE_DOC,
	INFILE,
	OUTFILE,
	APPENDFILE,
	DELIMITER
} token_type;

typedef struct s_token
{
	char *value;
	token_type type;
	struct s_token *next;
} t_token;

# include "ast.h"
# include "parsing.h"
# include "builtins.h"

t_token *lexer(char *input);
char **ft_clean_input(char **split_input);
char *ft_expand_envvar(const char *input);
t_token *tokenize(char **split_input);
void print_tokens(t_token *tokens);
int is_token_redirection(token_type token);
void    free_tokens(t_token *tokens);

int syntaxer(t_token *tokens);
int is_token_file(token_type token);
void print_ast(t_ast_node *node, int level);

void execute_ast(t_ast_node *root, char **envp);
void	ft_free_tab(char **tab);
char *get_type(int type);
char	*ft_get_path(char *cmd, char **envp);
void pre_process_heredocs(t_ast_node *root);
char *get_var_value(char *var_name);
char	*gnl(int fd);
char *build_prompt();
void ft_free_ast(t_ast_node *root);
void ft_free_redirection(t_redirection *redirection);
void    free_token(t_token *tokens);
#endif
