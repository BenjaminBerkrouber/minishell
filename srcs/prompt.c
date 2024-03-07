/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:04:29 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/07 17:04:43 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_host()
{
    char *line;
    char **tab;
    char *host;
    int fd;

    fd = open("/etc/hostname", O_RDONLY);
    if (fd == -1)
        return (NULL);
    line = gnl(fd);
    close(fd);
    if (!line)
        return (NULL);
    tab = ft_split(line, '.');
    free(line);
    if (!tab)
        return (NULL);
    if (!tab)
        return (NULL);
    host = strdup(tab[0]);
    ft_free_tab(tab);
    return (host);
}

char *get_path_prompt()
{
    char *pwd;
    char *home = getenv("HOME");
    char *path;
    size_t home_len;
    size_t res_size;

    pwd = getenv("PWD");
    home = getenv("HOME");
    if (!pwd || !home)
        return NULL;

    home_len = strlen(home);
    if (strncmp(pwd, home, home_len) == 0)
    {
        if (strlen(pwd) == home_len)
            path = strdup("~");
        else
        {
            res_size = strlen(pwd) - home_len + 2;
            path = malloc(res_size);
            if (!path)
                return (NULL);
            path[0] = '~';
            strcpy(path + 1, pwd + home_len);
        }
    }
    else
        path = strdup(pwd);

    return (path);
}
char *build_prompt()
{
    char *prompt;
    char *user;
    char *host;
    char *path;
    size_t total_length;
    
    path = get_path_prompt();
    user = get_var_value("USER");
    host = get_host();

    total_length = ft_strlen(user) + ft_strlen(host) + ft_strlen(path) + 3 + 1;

    prompt = malloc(total_length);
    if (!prompt)
    {
        free(user);
        free(host);
        return (NULL);
    }
    strcpy(prompt, user);
    strcat(prompt, "@");
    strcat(prompt, host);
    strcat(prompt, path);
    strcat(prompt, "$ ");
    free(user);
    free(host);
    free(path);
    return (prompt);
}