/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:21:24 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/20 21:39:14 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valide_parsing(char **args, char **envp)
{
    if (!args || !*args)
        return (1);
    if (!args[1])
    {
        perror("bash: cd: missing operand");
        return (1);
    }
    if (args[2])
    {
        perror("bash: too many args");
        return (1);
    }
    if (!envp)
        return (-1);
    return (0);
}

void    update_var_in_env(char *key_value, char *key, char ***envp)
{
    char *env_var;
    char *key;
    int i;

    i = 0;
    key = ft_strjoin(key, "=");
    env_var = ft_strjoin(key, key_value);
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], key_value, ft_strlen(key_value)) == 0)
        {
            free((*envp)[i]);
            (*envp)[i] = env_var;
        }
        i++;
    }
}

void    add_var_in_env(char *key_value, char *key, char ***envp)
{
    
}

int    search_var_in_env(char *key,char ***envp)
{
    int i;

    i = 0;
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], key, ft_strlen(key) - 1) == 0)
            return (1);
        i++;
    }
    return (0);
}

void    upadte_env(char *key_value, char *key ,char ***envp)
{
    if (search_var_in_env(key, envp))
        update_var_in_env(key_value, key, envp);
    else
        add_var_in_env(key_value, key, envp);
}

int ft_cd(char **args, char **envp)
{
    int exit_code;
    char *path;
    char *old_path;

    old_path = getcwd(NULL, 0);
    exit_code = is_valide_parsing(args, envp);
    if (exit_code != 0)
        return (exit_code);
    exit_code = chdir(args[1]);
    if (exit_code == -1)
    {
        perror("cd");
        return (1);
    }
    path = getcwd(NULL, 0);
    upadte_env(path, "PWD", &envp);
    upadte_env(old_path, "OLDPWD",&envp);
    return (exit_code);
}