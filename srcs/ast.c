/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2023/12/16 10:55:45 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *build_ast(t_token *tokens, int index, t_ast_node *current_node)
{
    if (tokens[index].token == NULL) {
        return current_node;
    }

    t_token token = tokens[index];
    t_ast_node *new_node = NULL;

    // Traitement des commandes et arguments
    if (token.type == TOKEN_COMMAND || token.type == TOKEN_WORD) {
        new_node = create_ast_node(token.type, token.token);
        if (current_node != NULL && (current_node->type == TOKEN_COMMAND || current_node->type == TOKEN_WORD)) {
            add_child_node(current_node, new_node);
        } else {
            current_node = new_node;
        }
    }

    // Traitement des redirections
    if (token.type == TOKEN_REDIRECT) {
        new_node = create_ast_node(token.type, token.token);
        if (current_node != NULL) {
            add_child_node(current_node, new_node);
            current_node = new_node;
        }
    }

    // Traitement des pipes
    if (token.type == TOKEN_PIPE) {
        new_node = create_ast_node(token.type, token.token);
        if (current_node != NULL) {
            t_ast_node *pipe_node = create_ast_node(TOKEN_PIPE, NULL);
            add_child_node(pipe_node, current_node);
            current_node = pipe_node;
        } else {
            current_node = new_node;
        }
    }

    return build_ast(tokens, index + 1, current_node);
}

