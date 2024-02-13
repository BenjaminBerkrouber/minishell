/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2023/12/20 06:33:18 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *create_ast_node(token_type type, char *value)
{
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node)
        return NULL;

    node->type = type;
    if (value)
        node->value = ft_strdup(value);
    else
        node->value = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

char *tokenize_command(t_token *tokens) {
    t_token *current = tokens;
    int total_length = 0;

    while (current != NULL) {
        total_length += strlen(current->value) + 1;
        current = current->next;
    }

    char *cmd_str = (char *)malloc(total_length * sizeof(char));
    if (!cmd_str) {
        return NULL;
    }
    cmd_str[0] = '\0';

    current = tokens;
    while (current != NULL)
    {
        strcat(cmd_str, current->value);
        if (current->next != NULL)
            strcat(cmd_str, " ");
        current = current->next;
    }

    return cmd_str; 
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
    {
        char *cmd = tokenize_command(tokens);
        root = create_ast_node(CMD, cmd);
        free(cmd);
    } 
    else 
    {
        right_token = cursor->next;
        cursor->next = NULL;
        root = create_ast_node(cursor->type, NULL);
        remove_token_split(tokens);
        left = build_ast(tokens);
        right = build_ast(right_token);
        root->left = left;
        root->right = right;
    }
    return (root);
}



