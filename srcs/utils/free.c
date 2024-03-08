/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:06:38 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/07 18:59:35 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_redirection(t_redirection *redirection)
{
    t_redirection *current;
    t_redirection *next;

    current = redirection;
    while (current)
    {
        next = current->next;
        if (current->filename)
            free(current->filename);
        free(current);
        current = next;
    }
}

void    free_tokens(t_token *tokens)
{
    t_token *tmp;

    if (!tokens)
        return ;
    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}


void ft_free_ast(t_ast_node *node)
{
    if (!node)
        return;
    ft_free_ast(node->left);
    ft_free_ast(node->right);
    if (node->token)
        free_tokens(node->token);
    if (node->redirections)
        ft_free_redirection(node->redirections);
    free(node);
}