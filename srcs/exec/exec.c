/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:52:08 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/09 01:05:24 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_args(t_token *token)
{
    char **args;
    int i;
    t_token *cursor;

    if (!token)
        return (NULL);
    cursor = token;
    i = 0;
    while (cursor)
    {
        i++;
        cursor = cursor->next;
    }
    args = malloc(sizeof(char *) * (i + 1));
    i = 0;
    cursor = token;
    while (cursor)
    {
        args[i] = cursor->value;
        i++;
        cursor = cursor->next;
    }
    args[i] = NULL;
    return (args);
}


static int exec_command(t_ast_node *root, int in_fd, int *pipe_fds, char **envp)
{
    pid_t       pid;
    char        *path;
    char        **args;
    int         status_fd;
    t_ast_node  *node;

    if (root->left)
        node = root->left;
    else 
        node = root;
    path = NULL;
    args = NULL;
    pid = fork();
    if (pid == 0)
    {
        if (in_fd != STDIN_FILENO)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (pipe_fds[1] != STDOUT_FILENO)
        {
            dup2(pipe_fds[1], STDOUT_FILENO);
            close(pipe_fds[1]);
        }
        if (pipe_fds[0] > 2)
            close(pipe_fds[0]);
        status_fd = setup_redirections(node->redirections);
        if (!node->token || status_fd == 1)
        {
            ft_free_ast(root);
            exit(status_fd);
        }
        path = ft_get_path(node->token->value, envp);
        if (!path)
        {
            ft_putstr_fd(node->token->value, 2);
            if (ft_strncmp(get_var_value("PATH"), "\0", 1) == 0)
                ft_putstr_fd(": No such file or directory\n", 2);
            else
                ft_putstr_fd(": command not found\n", 2);
            ft_free_ast(root);
            exit(127);
        }
        args = get_args(node->token);
        if (execve(path, args, envp) == -1)
        {
            perror(path);
            if (path)
                free(path);
            if (args)
                ft_free_tab(args);
            exit(1);
        }
        if (path)
            free(path);
        if (args)
            ft_free_tab(args);
    }
    return (pid);
}

void exec_pipeline(t_ast_node *node, char **envp, int fd_in)
{
    int	pipe_fds[2];
    int	pid;
    int	err_code;
    t_ast_node *tmp;
    
    if (node == NULL)
        return ;
    if (node->type == PIPE)
    {
        pipe(pipe_fds);
        pid = exec_command(node, fd_in, pipe_fds, envp);
        close(pipe_fds[1]);
        if (fd_in > 2)
            close(fd_in);
        ft_free_ast(node->left);
        tmp = node->right;
        if (node->token)
            free_tokens(node->token);
        if (node->redirections)
            ft_free_redirection(node->redirections);
        free(node);
        exec_pipeline(tmp, envp, pipe_fds[0]);
        waitpid(pid, &err_code, 0);
    }
    else
    {
        pipe_fds[0] = -1;
        pipe_fds[1] = STDOUT_FILENO;
        pid = exec_command(node, fd_in, pipe_fds, envp);
        if (fd_in > 2)
            close(fd_in);
        ft_free_ast(node);
        waitpid(pid, &err_code, 0);
        if (WIFEXITED(err_code))
            g_last_exit_status = WEXITSTATUS(err_code);
    }
}

void execute_ast(t_ast_node *root, char **envp)
{
    pre_process_heredocs(root);
    exec_pipeline(root, envp, STDIN_FILENO);    
}
