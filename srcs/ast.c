/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/26 18:37:19 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *copy_token(t_token *src)
{
    t_token *dst;

    if (src == NULL)
        return NULL;
    dst = malloc(sizeof(t_token));
    if (dst == NULL)
        return NULL;
    dst->type = src->type;
    dst->next = src->next;
    if (src->value != NULL)
    {
        dst->value = strdup(src->value);
        if (dst->value == NULL)
        {
            free(dst);
            return NULL;
        }
    } else
        dst->value = NULL;

    return (dst);
}

t_ast_node *create_ast_node(t_token *token)
{
    t_ast_node *node;
    
    node = malloc(sizeof(t_ast_node));
    if (!node)
        return NULL;
    node->type = token->type;
    if (token)
        node->token = copy_token(token);
    else
        node->token = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

int is_split_token(token_type token)
{
    return (token == PIPE);
}

void    remove_token_split(t_token *tokens)
{
    t_token *target;

    if (!tokens)
        return ;
    while (tokens->next && !is_split_token(tokens->next->type))
        tokens = tokens->next;
    target = tokens->next;
    tokens->next = NULL;
    free(target->value);
    free(target);
}

t_ast_node *build_ast(t_token *tokens)
{
    t_token *cursor = tokens;
    t_token *right_token = NULL;
    t_ast_node *root = NULL;
    t_ast_node *left = NULL;
    t_ast_node *right = NULL;
    
    if (!tokens)
        return NULL;
    while (cursor != NULL && !is_split_token(cursor->type))
        cursor = cursor->next;
    if (cursor == NULL)
        root = create_ast_node(tokens);
    else 
    {
        right_token = cursor->next;
        cursor->next = NULL;
        root = create_ast_node(cursor);
        remove_token_split(tokens);
        left = build_ast(tokens);
        right = build_ast(right_token);
        root->left = left;
        root->right = right;
    }
    return (root);
}



