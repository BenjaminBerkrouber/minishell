/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:04:21 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/23 08:04:40 by bberkrou         ###   ########.fr       */
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

// int main(int argc, char *argv[])
// {
//     t_token *tokens;
//     t_ast_node *ast;
//     char *command;

//     (void)argc;
//     (void)argv;
//     (void)ast;

//     while (1)
//     {
//         command = readline("> ");
//         if (!command)
//             break; 
//         add_history(command);
//         tokens = lexer(command);
//         if (!tokens || !is_valide_token(tokens))
//         {
//             free_tokens(tokens);
//             free(command);
//             continue;
//         }
//         print_tokens(tokens);

//         // ast = build_ast(tokens);
//         // print_ast(ast, 0);
//         free_tokens(tokens);
//         free(command);
//     }
//     return 0;
// }

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char **env;

    env = copy_envp(envp);
    (void)env;
    // ft_pwd(argv, envp);
    ft_pwd(NULL, envp);
    printf("%d\n", ft_cd(argv, env));
    ft_pwd(NULL, envp);
    // ft_unset(argv, env);
    ft_env(NULL, env);
    return (0);
}