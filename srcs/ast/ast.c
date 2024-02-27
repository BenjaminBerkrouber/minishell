/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/27 16:56:51 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection *get_pars_redirection(t_token **token)
{
    t_redirection *redirection;
    t_token *cursor;
    t_redirection_type type;

    if (!token || !*token)
        return (NULL);
    redirection = NULL;
    cursor = *token;
    while (cursor)
    {
        if (cursor->next && is_token_redirection(cursor->next->type))
        {
            type = ft_type_to_redirection(cursor->next->type);
            ft_redirectionadd_back(&redirection,
                ft_redirection_new(cursor->next->next->value, type));
            cursor->next = cursor->next->next->next;
        }
        else
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
    node->redirections = redirection = get_pars_redirection(&token);
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



