/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:10:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/26 18:36:58 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct s_ast_node {
    token_type type;
    t_token *token;
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;


t_ast_node *build_ast(t_token *tokens);
t_ast_node *create_ast_node(t_token *token);
