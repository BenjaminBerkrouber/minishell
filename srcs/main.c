/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/16 03:27:52 by bberkrou         ###   ########.fr       */
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

void print_ast(t_ast_node *node, int level)
{
    if (node == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("    ");

    switch (node->type) 
    {
        case CMD:
            printf("CMD: %s\n", node->value);
            break;
        case PIPE:
            printf("PIPE\n");
            break;
        case REDIRECT_IN:
            printf("REDIRECT_IN: %s\n", node->value);
            break;
        case REDIRECT_OUT:
            printf("REDIRECT_OUT: %s\n", node->value);
            break;
        case REDIRECT_APPEND:
            printf("REDIRECT_APPEND: %s\n", node->value);
            break;
        case HERE_DOC:
            printf("HERE_DOC: %s\n", node->value);
            break;
        default:
            printf("UNKNOWN\n");
    }

    if (node->left != NULL) {
        print_ast(node->left, level + 1);
    }
    if (node->right != NULL) {
        print_ast(node->right, level + 1);
    }
}

int is_token_redirection(token_type token)
{
    return (token == PIPE ||
        token == REDIRECT_IN ||
        token == REDIRECT_OUT ||
        token == REDIRECT_APPEND ||
        token == HERE_DOC);
}

int is_valide_token(t_token *tokens)
{
    t_token *current = tokens;

    if (!current)
    {
        printf("bash: erreur de syntaxe près du symbole inattendu « newline »\n");
        return 0;
    }
    if (current->type == PIPE)
    {
        printf("bash: erreur de syntaxe près du symbole inattendu « %s »\n", current->value);   
        return 0;
    }
    while (current)
    {
        if (is_token_redirection(current->type))
        {
            if (!current->next)
            {
                printf("bash: erreur de syntaxe près du symbole inattendu « newline »\n"); 
                return 0;
            }
            if (is_token_redirection(current->next->type))
            {
                printf("bash: erreur de syntaxe près du symbole inattendu « %s »\n", current->next->value);    
                return 0;
            }
        }
        current = current->next;
    }
    return 1;
}


int main(int argc, char *argv[])
{
    t_token *tokens;
    // t_ast_node *ast;
    char *command;

    (void)argc;
    (void)argv;

    while (1)
    {
        command = readline("> ");
        if (!command)
            break; 

        tokens = lexer(command);
        if (!tokens || !is_valide_token(tokens))
        {
            free_tokens(tokens);
            free(command);
            continue;
        }
        print_tokens(tokens);

        // ast = build_ast(tokens);
        // print_ast(ast, 0);
        free_tokens(tokens);
        free(command);
    }
    return 0;
}
