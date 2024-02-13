/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2023/12/20 06:33:18 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_setenv(char *name, char *value, char ***env)
{
    char    *env_str;
    char    **new_env;
    int     i;

    env_str = ft_strjoin(name, "=");
    env_str = ft_strjoin(env_str, value);
    i = 0;
    while ((*env)[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * (i + 2));
    i = 0;
    while ((*env)[i])
    {
        new_env[i] = ft_strdup((*env)[i]);
        i++;
    }
    new_env[i] = ft_strdup(env_str);
    new_env[i + 1] = NULL;
    free(*env);
    *env = new_env;
}

void    ft_addenv(char *name, char *value, char ***env)
{
    char    *env_str;
    char    **new_env;
    int     i;

    env_str = ft_strjoin(name, "=");
    env_str = ft_strjoin(env_str, value);
    i = 0;
    while ((*env)[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * (i + 2));
    i = 0;
    while ((*env)[i])
    {
        new_env[i] = ft_strdup((*env)[i]);
        i++;
    }
    new_env[i] = ft_strdup(env_str);
    new_env[i + 1] = NULL;
    free(*env);
    *env = new_env;
}

ft_strtok(char *str, char *delim)
{
    static char *s;
    char *ret;
    int i;

    if (str)
        s = str;
    if (!s || !*s)
        return NULL;
    i = 0;
    while (s[i] && !ft_strchr(delim, s[i]))
        i++;
    ret = (char *)malloc(sizeof(char) * (i + 1));
    ft_strlcpy(ret, s, i + 1);
    s += i;
    while (*s && ft_strchr(delim, *s))
        s++;
    return ret;
}

void ft_export(char **args, char ***env)
{
    int i;
    char *name;
    char *value;

    i = 0;
    while (args[i])
    {
        name = ft_strtok(args[i], "=");
        value = ft_strtok(NULL, "=");
        if (value)
            ft_setenv(name, value, env);
        else
            ft_addenv(name, "", env);
        i++;
    }

}