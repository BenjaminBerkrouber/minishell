/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 14:26:20 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
    t_token *tokens;
    t_ast_node *ast;
    char *command;
    t_redirection *redirection;
    char *prompt;

    (void)argc;
    (void)argv;
    (void)ast;
    (void)tokens;
    (void)envp;
    (void)command;
    (void)redirection;

    while (1)
    {
        prompt = build_prompt();
        command = readline(prompt);
        free(prompt);
        if (!command)
            break; 
        add_history(command);
        if (ft_strncmp(command, "aaa", 3 ) == 0)
        {
            free(command);
            break;
        }
        tokens = lexer(command);
        if (!tokens || !syntaxer(tokens))
        {
            free_tokens(tokens);
            free(command);
            continue;
        }

        // printf("\n==================TOKENS==================\n\n");
        print_tokens(tokens);

        ast = build_ast(&tokens);
        // printf("\n===================AST===================\n\n");
        // print_ast(ast, 0);

        // printf("\n==================Exec===================\n\n");
                // print_tokens(tokens);

        execute_ast(ast, envp);
        // ft_free_ast(ast);

        
        // free_tokens(tokens);
        //printf("%s", tokens->value);
        free(command);
        
    }
    return 0;
}