/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 19:01:19 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_type(int type)
{
    switch (type)
    {
    case CMD:
        return "CMD";
    case OPTION:
        return "OPTION";
    case ARGUMENT:
        return "ARGUMENT";
    case PIPE:
        return "PIPE";
    case REDIRECT_IN:
        return "REDIRECT_IN";
    case REDIRECT_OUT:
        return "REDIRECT_OUT";
    case REDIRECT_APPEND:
        return "REDIRECT_APPEND";
    case HERE_DOC:
        return "HERE_DOC";
    case INFILE:
        return "INFILE";
    case OUTFILE:
        return "OUTFILE";
    case APPENDFILE:
        return "APPENDFILE";
    case DELIMITER:
        return "DELIMITER";
    default:
        return "UNKNOWN";
    }
}

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        printf("[%s {%s}]\n", tokens->value, get_type(tokens->type));
        tokens = tokens->next;
    }
    printf("\n");
}

void    free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}

int main(int argc, char *argv[])
{
    t_token *tokens;
    char *command;

    (void)argc;
    (void)argv;

    while (1) {
        command = readline("> ");
        if (!command)
            break;

        tokens = lexer(command);
        print_tokens(tokens);
        free_tokens(tokens);
        free(command);
    }
    return 0;
}
