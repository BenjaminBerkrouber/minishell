/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:38:43 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/26 17:25:24 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_or_and_operator(char **input, char ***split_input, int *i)
{
    if (**input == '|' && *(*input + 1) == '|')
    {
        (*split_input)[*i] = strndup(*input, 2);
        *input += 2;
        (*i)++;
    }
    else if (**input == '&' && *(*input + 1) == '&')
    {
        (*split_input)[*i] = strndup(*input, 2);
        *input += 2;
        (*i)++;
    }
}

char **split_and_or(char *input)
{
    char **split_input;
    int i = 0;
    int j = 0;
    
    split_input = malloc(sizeof(char *) * 100);
    if (!split_input)
        return (NULL);

    while (*input)
    {
        j = 0;
        while (input[j] && !(input[j] == '|' && input[j + 1] == '|') && !(input[j] == '&' && input[j + 1] == '&'))
            j++;
        if (j > 0)
            split_input[i++] = strndup(input, j);
        input += j;
        if (*input == '|' || *input == '&')
            add_or_and_operator(&input, &split_input, &i);
    }
    split_input[i] = NULL;
    return (split_input);
}

int is_valide_input(char *input)
{
    t_token *token_list;

    token_list = lexer(input);
    if (!token_list)
        return (0);
    free_tokens(token_list);
    return (1);
}

t_token *split_to_tokens(char **split_input)
{
    t_token *token_list;
    int i;

    i = 0;

    while (split_input[i])
    {
        if (ft_strncmp(split_input[i] , "||", 2) == 0)
            add_token(&token_list, new_token(split_input[i], OR));
        else if (ft_strncmp(split_input[i] , "&&", 2) == 0)
            add_token(&token_list, new_token(split_input[i], AND));
        else
            add_token(&token_list, new_token(split_input[i], CMD));
        i++;
    }
    return (token_list);
}

t_ast_node *process(char *input)
{
    char **split_input;
    t_token *tokens;
    t_ast_node *root;

    split_input = NULL;
    root = NULL;
    if (is_valide_input(input))
        split_input = split_and_or(input);
    if (!split_input)
        return (NULL);
    tokens = split_to_tokens(split_input);
    // print_tokens(tokens);
    if (!tokens)
        return (NULL);
    root = build_ast(tokens);
    if (!root)
        return (NULL);
    return (root);
}