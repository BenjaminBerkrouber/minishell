/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:30:09 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/07 19:00:29 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int is_split_token(token_type token)
{
    return (token == PIPE);
}
