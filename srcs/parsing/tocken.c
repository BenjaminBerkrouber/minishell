/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:24:17 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 12:56:15 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_map token_map[] = {
    {";", TOKEN_OPERATOR},
    {"&&", TOKEN_OPERATOR},
    {"||", TOKEN_OPERATOR},
    {"|", TOKEN_PIPE},
    {">", TOKEN_REDIRECT},
    {"<", TOKEN_REDIRECT},
    {">>", TOKEN_REDIRECT},
    {"<<", TOKEN_REDIRECT},
    {NULL, TOKEN_WORD}
};

int get_token_length(char *input)
{
    int length;
    int in_quotes;

    length = 0;
    in_quotes = 0;

    while (*input && ((*input != ' ') || (*input == ' ' && in_quotes)))
    {
        if (*input == '\"')
            in_quotes = !in_quotes;
        input++;
        length++;
    }
    return (length);
}

const char *getTokenTypeName(t_token_type type)
{
    switch (type) {
        case TOKEN_WORD:
            return "Word";
        case TOKEN_OPERATOR:
            return "Operator";
        case TOKEN_REDIRECT:
            return "Redirect";
        case TOKEN_COMMAND:
            return "Command";
		case TOKEN_PIPE:
			return "Pipe";
		case TOKEN_END:
			return "End";
		case TOKEN_ENVVAR:
			return "Envvar";
        case TOKEN_ROOT:
            return "Root";
        default:
            return "Unknown";
    }
}