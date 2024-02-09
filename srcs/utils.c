/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:23:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 19:09:36 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

const char *skip_spaces(const char *input)
{
    while (*input == ' ') 
        input++;
    return input;
}

int is_meta_char(char *c)
{
    if (strncmp(c, "|", 1) == 0)
        return PIPE;
    if (strncmp(c, "<", 1) == 0)
        return REDIRECT_IN;
    if (strncmp(c, ">", 1) == 0)
        return REDIRECT_OUT;
    if (strncmp(c, ">>", 2) == 0)
        return REDIRECT_APPEND;
    if (strncmp(c, "<<", 2) == 0)
        return HERE_DOC;
    return 0;
}