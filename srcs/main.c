/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/17 05:07:56 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[])
{
    t_token *tokens;
    t_ast_node *ast;
    char *command;

    (void)argc;
    (void)argv;

    while (1)
    {
        command = readline("> ");
        if (!command)
            break; 
        add_history(command);
        tokens = lexer(command);
        if (!tokens || !is_valide_token(tokens))
        {
            free_tokens(tokens);
            free(command);
            continue;
        }
        print_tokens(tokens);

        ast = build_ast(tokens);
        print_ast(ast, 0);
        free_tokens(tokens);
        free(command);
    }
    return 0;
}
