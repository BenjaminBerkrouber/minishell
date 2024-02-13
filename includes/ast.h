/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:10:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 18:57:08 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct s_ast_node {
    token_type type;
    char *value;
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;


t_ast_node *build_ast(t_token *tokens);
t_ast_node *create_ast_node(token_type type, char *value);
