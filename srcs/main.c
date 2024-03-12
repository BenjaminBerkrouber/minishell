/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/12 16:35:08 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_sig(int sign_num)
{
    if (sign_num == SIGINT)
    {
        ft_putchar_fd('\n', 1);
        g_last_exit_status = 1;
        printf("%s", build_prompt());
    }
    else if (sign_num == SIGQUIT)
        ft_putstr_fd("\b\b  \b\b", 1);
}

void    process_sig_muted(int sign_num)
{
    if (sign_num == SIGINT)
    {
        ft_putchar_fd('\n', 1);
        g_last_exit_status = 1;
        printf("%s", build_prompt());
    }
    else if (sign_num == SIGQUIT)
        ft_putstr_fd("\b\b  \b\b", 1);
}

int main(int argc, char *argv[], char **envp)
{
    char            *prompt;
    char            *command;
    t_token         *tokens;
    t_ast_node      *ast;
    t_redirection   *redirection;

    (void)argc;
    (void)argv;
    (void)ast;
    (void)tokens;
    (void)envp;
    (void)command;
    (void)redirection;

    signal(SIGINT, process_sig_muted);

    while (1)
    {
        prompt = build_prompt();
        command = readline(prompt);

        signal(SIGINT, process_sig_muted);

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
        // print_tokens(tokens);

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


