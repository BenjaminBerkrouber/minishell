/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:24:17 by bberkrou          #+#    #+#             */
/*   Updated: 2023/12/16 10:41:59 by bberkrou         ###   ########.fr       */
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

t_token *creerToken(char *text, t_token_type type)
{
    t_token *nouveauToken = malloc(sizeof(t_token));
    if (nouveauToken != NULL)
    {
        nouveauToken->token = strdup(text);
        nouveauToken->type = type;
    }
    return nouveauToken;
}

t_token_type get_token_type(char *token)
{
	int i;

    if (token[0] == '$')
    {
        return (TOKEN_ENVVAR);
    }
	i = 0;
    while (token_map[i].token_str != NULL)
	{
        if (strcmp(token, token_map[i].token_str) == 0)
            return token_map[i].token_type;
		i++;
	}

    if (is_command(token))
        return TOKEN_COMMAND;

    return TOKEN_WORD;
}

const char *skip_spaces(const char *input)
{
    while (*input == ' ') 
        input++;
    return input;
}

int get_token_length(const char *input, int inQuotes)
{
    int length = 0;
    while (*input && (inQuotes ? (*input != '\"') : (*input != ' ')))
	{
        length++;
        input++;
    }
    return (length);
}

const char *create_and_add_token(t_token *tokens, int *tokenIndex, char *tokenStart, int length)
{
    char *newTokenStr;
    if (length > 0) {
        newTokenStr = strndup(tokenStart, length);
        tokens[*tokenIndex] = *creerToken(newTokenStr, get_token_type(newTokenStr));
        free(newTokenStr);
        (*tokenIndex)++;
    }
    return tokenStart + length;
}

t_token *tokenize(const char *input)
{
    t_token *tokens;
    int tokenIndex = 0;
    char *tokenStart;
    int inQuotes;
    int length;

    tokens = malloc(100 * sizeof(t_token));
    if (tokens == NULL)
        return NULL;

    while (*input) {
        inQuotes = 0;
        input = skip_spaces(input);
        tokenStart = (char *)input;
        if (*input == '\"') {
            inQuotes = 1;
            tokenStart++;
            input++;
        }
        length = get_token_length(input, inQuotes);
        input = create_and_add_token(tokens, &tokenIndex, tokenStart, length);
        if (inQuotes && *input) 
            input++;
    }
    tokens[tokenIndex].token = NULL;
    return tokens;
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