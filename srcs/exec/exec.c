/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:52:08 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/27 17:14:52 by bberkrou         ###   ########.fr       */
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

static void setup_redirections(t_redirection *redirections)
{
    int fd;

    while (redirections)
    {
        if (redirections->type == T_REDIRECT_OUT)
        {
            fd = open(redirections->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redirections->type == T_APPEND)
        {
            fd = open(redirections->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redirections->type == T_REDIRECT_IN)
        {
            fd = open(redirections->filename, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        redirections = redirections->next;
    }
}


static int exec_command(t_ast_node *node, int in_fd, int out_fd, char **envp)
{
    pid_t pid;
    char *path;
    char **args;

    pid = fork();
    if (pid == 0)
    {
        setup_redirections(node->redirections);

        if (in_fd != STDIN_FILENO)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO)
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        path = ft_get_path(node->token->value, envp);
        args = get_args(node->token); 
        if (execve(path, args, envp) == -1)
        {
            if (path)
			    free(path);
            if (args)
            ft_free_tab(args);
		    perror("Error: Command not found\n");
            exit(EXIT_FAILURE);
        }
        if (path)
            free(path);
        if (args)
            ft_free_tab(args);
    }
    return (pid);
}

static void exec_pipeline(t_ast_node *node, char **envp, int fd_in)
{
    int pipe_fds[2];
    int pid;
    int err_code;
    
    if (node == NULL)
        return;
    if (node->type == PIPE)
    {
        pipe(pipe_fds);
        pid = exec_command(node->left, fd_in, pipe_fds[1], envp);
        close(pipe_fds[1]);
        if (fd_in > 2)
            close(fd_in);
        exec_pipeline(node->right, envp, pipe_fds[0]);
        close(pipe_fds[0]);
        waitpid(pid, &err_code, 0);
    }
    else
    {
        pid = exec_command(node, fd_in, STDOUT_FILENO, envp);
        if (fd_in > 2)
            close(fd_in);
        waitpid(pid, &err_code, 0);
    }
}

void execute_ast(t_ast_node *node, char **envp)
{
    exec_pipeline(node, envp, STDIN_FILENO);
}
