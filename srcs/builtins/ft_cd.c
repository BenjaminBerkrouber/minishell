/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:21:24 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/17 05:27:38 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *build_path(char *reltive_path)
{
    char *absolut_path;
    char *current_path;
    size_t current_path_len;
    size_t reltive_path_len;
    
    current_path = getcwd(NULL, 0);
    if (!current_path)
        return (NULL);
    current_path_len = ft_strlen(current_path);
    reltive_path_len = ft_strlen(reltive_path);
    absolut_path = malloc(current_path_len + reltive_path_len + 2);
    if (!absolut_path)
    {
        free(current_path);
        return (NULL);
    }
    strcpy(absolut_path, current_path);
    absolut_path[current_path_len] = '/';
    strcpy(absolut_path + current_path_len + 1, reltive_path);
    free(current_path);
    return (absolut_path);
}

char *get_path(char *path)
{
    if (path[0] == '/')
        return (ft_strdup(path));
    return (build_path(path));
}

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

// gere le cas ou pwd or oldpwd nexiste pas
void    upadte_env(char *path, char *old_path, char ***envp)
{
    char *oldpwd_str;
    char *pwd_str;
    int i;

    i = 0;
    oldpwd_str = ft_strjoin("OLDPWD=", old_path);
    pwd_str = ft_strjoin("PWD=", path);
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], "OLDPWD=", 7) == 0)
        {
            free((*envp)[i]);
            (*envp)[i] = oldpwd_str;
        }
        else if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
        {
            free((*envp)[i]);
            (*envp)[i] = pwd_str;
        }
        i++;
    }
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
    path = build_path(args[1]);
    if (!path)
    {
        perror("Error : Allocated failed");
        return (-1);
    }
    exit_code = chdir(path);
    if (exit_code == -1)
    {
        fprintf(stderr, "bash: cd: %s: Aucun fichier ou dossier de ce type", args[1]);
        return (1);
    }
    ft_pwd();
    upadte_env(path, old_path, &envp);
    ft_env(NULL, envp);
    return (exit_code);
}