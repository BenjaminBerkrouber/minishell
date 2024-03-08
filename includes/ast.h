/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:10:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 18:40:54 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_redirection_type {
    T_REDIRECT_NONE,
    T_REDIRECT_IN,
    T_REDIRECT_OUT,
    T_APPEND,
    T_HEREDOC
} t_redirection_type;

typedef struct s_redirection {
    t_redirection_type type;
    char *filename;
    struct s_redirection *next;
} t_redirection;

typedef struct s_ast_node {
    token_type type;
    t_token *token;
    struct s_ast_node *left;
    struct s_ast_node *right;
    t_redirection *redirections;
} t_ast_node;


t_ast_node *build_ast(t_token **tokens);
t_ast_node *create_ast_node(t_token **token);

t_token *copy_token(t_token *src);
void    remove_token_split(t_token *tokens);
int is_split_token(token_type token);

t_redirection_type ft_type_to_redirection(token_type token);
void ft_redirectionadd_back(t_redirection **redirection_lst, t_redirection *new);
t_redirection	*ft_redirection_new(char *filename, t_redirection_type type);
t_redirection *get_pars_redirection(t_token **token);
int setup_redirections(t_redirection *redirections);
