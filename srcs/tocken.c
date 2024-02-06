/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:24:17 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/06 19:00:50 by bberkrou         ###   ########.fr       */
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

const char *create_and_add_token(t_token *tokens, int *tokenIndex, char *tokenStart, int length)
{
    char    *newTokenStr;
    
    if (length > 0) {
        newTokenStr = strndup(tokenStart, length);
        tokens[*tokenIndex] = *creerToken(newTokenStr, get_token_type(newTokenStr));
        free(newTokenStr);
        (*tokenIndex)++;
    }
    return tokenStart + length;
}

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

void print_split_input(char **split_input)
{
    int i;

    i = 0;
    while (split_input[i])
    {
        printf("[%s]\n", split_input[i]);
        i++;
    }
}

char **ft_split_input(char *input)
{
    char    **split_input;
    int     lenght;
    int     i;

    i = 0;
    lenght = 0;
    split_input = malloc(sizeof(char *) * 100);
    while (*input )
    {
        lenght = get_token_length(input);
        input += lenght;
        if (lenght > 0)
        {
            split_input[i] = strndup(input - lenght, lenght);
            i++;
        }
        if (*input == ' ')
            input++;
    }
    split_input[i] = NULL;
    return (split_input);
}



t_token *tokenize(char *input)
{
    // char **split_input;
    char *input_expend;
    
    input_expend = ft_expand_envvar(input);
    printf("%s\n", input_expend);
    // split_input = ft_split_input(input_expend);
    // split_input = ft_clean_input(split_input);
    // print_split_input(split_input);
    return (NULL);
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