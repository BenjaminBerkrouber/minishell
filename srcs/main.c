/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2023/12/16 13:26:10 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_ast(t_ast_node *node, int level)
{
    for (int i = 0; i < level; i++)
        printf("   ");
    printf("[%s] %s\n", getTokenTypeName(node->type), node->value);
    for (int i = 0; i < node->children_count; i++)
        print_ast(node->children[i], level + 1);
}

int main(int argc, char *argv[])
{
    t_token *tokens;
    // t_ast_node *ast_root;
    char *command;

    (void)argc;
    (void)argv;

    while (1) {
        command = readline("> ");

        if (!command) break;

        tokens = tokenize(command);
        
        for (int i = 0; tokens[i].token != NULL; i++){
            printf("[%s]", getTokenTypeName(tokens[i].type));
            printf(" %s\n", tokens[i].token);
        }
        // ast_root = build_ast(tokens, 0, NULL);
        // print_ast(ast_root, 0);
        libererTokens(tokens);
        free(command);
    }
    return 0;
}

