/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:52:11 by bberkrou          #+#    #+#             */
/*   Updated: 2023/12/16 10:56:40 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREE_H
# define THREE_H

# include "minishell.h"

typedef enum s_token_type{
    TOKEN_WORD,
	TOKEN_COMMAND,
    TOKEN_OPERATOR,
    TOKEN_REDIRECT,
	TOKEN_PIPE,
	TOKEN_END,
	TOKEN_ENVVAR,
    TOKEN_ROOT,
} t_token_type;

typedef struct s_token_map {
    char *token_str;
    t_token_type token_type;
} t_token_map;

typedef struct s_token{
    char *token;
	t_token_type type;
} t_token;

typedef struct s_ast_node {
    t_token_type type;
    char *value;
    struct s_ast_node **children;
    int children_count;
} t_ast_node;

t_ast_node *build_ast(t_token *tokens, int index, t_ast_node *current_node);
t_ast_node *create_ast_node(t_token_type type, char *value);
void add_child_node(t_ast_node *parent, t_ast_node *child);
void free_ast_node(t_ast_node *node);

#endif