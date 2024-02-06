/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:23:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/01/31 18:35:31 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void libererTokens(t_token	 *tokens)
{
	int i;

	i = 0;
    while (tokens[i].token != NULL)
	{
        free(tokens[i].token);
		i++;
    }
    free(tokens);
}

int is_command(char *token)
{
    if (strchr(token, '/') != NULL) 
        return access(token, X_OK) == 0;

    char *path = getenv("PATH");
    if (!path)
        return 0;

    char *path_copy = strdup(path);
    if (!path_copy) return 0;

    char *dir = strtok(path_copy, ":");
    while (dir != NULL) {
        char *full_path = malloc(strlen(dir) + strlen(token) + 2);
        if (full_path) {
            sprintf(full_path, "%s/%s", dir, token);
            if (access(full_path, X_OK) == 0) {
                free(full_path);
                free(path_copy);
                return 1;
            }
            free(full_path);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return 0;
}

// char *clean_cmd(char *cmd)
// {
//     char *clean_cmd;

    
//     return (clean_cmd);
// }
