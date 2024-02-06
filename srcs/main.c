/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2024/01/31 19:38:18 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char *argv[])
{
    // t_token *tokens;
    char *command;

    (void)argc;
    (void)argv;

    while (1) {
        command = readline("> ");
        // command = clean_cmd(command);
        if (!command) break;

        tokenize(command);
        
        // for (int i = 0; tokens[i].token != NULL; i++){
        //     // printf("[%s]", getTokenTypeName(tokens[i].type));
        //     printf("[%s] ", tokens[i].token);
        // }
        // libererTokens(tokens);
        free(command);
    }
    return 0;
}

// ls ls

// [ls, ls]

// " "

// [" "]

// " '"

// " lol ""

//     "ls '"

// [ls ']
