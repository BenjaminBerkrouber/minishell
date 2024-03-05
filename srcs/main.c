/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/05 10:53:34 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_envp(char **envp)
{
    int i;
    char **new_envp;
    
    for (i = 0; envp[i] != NULL; i++);
    new_envp = malloc(sizeof(char *) * (i + 1));
    if (!new_envp)
        return (NULL);
    for (i = 0; envp[i] != NULL; i++)
    {
        new_envp[i] = ft_strdup(envp[i]);
        if (!new_envp[i])
        {
            perror("error memory");
        }
    }
    new_envp[i] = NULL;
    return (new_envp);
}

void ft_free_redirection(t_redirection *redirection)
{
    t_redirection *current;
    t_redirection *next;

    current = redirection;
    while (current)
    {
        next = current->next;
        if (current->filename)
            free(current->filename);
        free(current);
        current = next;
    }
}

void ft_free_ast(t_ast_node *node)
{
    if (!node)
        return;
    ft_free_ast(node->left);
    ft_free_ast(node->right);
    if (node->token)
        free_tokens(node->token);
    if (node->redirections)
        ft_free_redirection(node->redirections);
    free(node);
}

int main(int argc, char *argv[], char **envp)
{
    t_token *tokens;
    t_ast_node *ast;
    char *command;
    t_redirection *redirection;

    (void)argc;
    (void)argv;
    (void)ast;
    (void)tokens;
    (void)envp;
    (void)command;
    (void)redirection;

    while (1)
    {
        command = readline("> ");
        if (!command)
            break; 
        add_history(command);
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
        printf("\n===================AST===================\n\n");
        print_ast(ast, 0);

        // printf("\n==================Exec===================\n\n");
                // print_tokens(tokens);

        execute_ast(ast, envp);
        // free_tokens(tokens);
        ft_free_ast(ast);
        free(command);
    }
    return 0;
}

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     printf("%s \n", ft_get_path(argv[1], envp));
// }