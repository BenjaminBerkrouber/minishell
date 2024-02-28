/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/28 04:27:18 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection *get_parse_redirection(t_token **token)
{
    t_redirection *redirection;
    t_token *cursor;
    t_token *prev;
    t_redirection_type type;
    t_token *to_remove;
    
    cursor = *token;
    prev = NULL;
    redirection = NULL;
    while (cursor)
    {
        if (is_token_redirection(cursor->type))
        {
            type = ft_type_to_redirection(cursor->type);
            if (cursor->next)
            {
                ft_redirectionadd_back(&redirection,
                    ft_redirection_new(ft_strdup(cursor->next->value), type));
                to_remove = cursor->next;
                cursor->next = cursor->next->next;
                if (prev)
                    prev->next = cursor->next;
                else
                    *token = cursor->next;
                free(to_remove->value);
                free(to_remove);
                continue;
            }
        }
        prev = cursor;
        cursor = cursor->next;
    }
    return (redirection);
}

t_ast_node *create_ast_node(t_token *token)
{
    t_ast_node *node;
    t_redirection *redirection;
    
    node = malloc(sizeof(t_ast_node));
    if (!node)
        return NULL;
    node->type = token->type;
    node->redirections = redirection = get_parse_redirection(&token);
    if (token)
        node->token = copy_token(token);
    else
        node->token = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
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



