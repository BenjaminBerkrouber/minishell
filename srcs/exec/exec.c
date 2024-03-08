/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:52:08 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 14:26:07 by bberkrou         ###   ########.fr       */
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


static int exec_command(t_ast_node *node, int in_fd, int *pipe_fds, char **envp)
{
    pid_t pid;
    char *path;
    char **args;

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
        setup_redirections(node->redirections);
        if (!node->token)
            exit(0);
        path = ft_get_path(node->token->value, envp);
        if (!path)
        {
            ft_putstr_fd(node->token->value, 2);
            if (ft_strncmp(get_var_value("PATH"), "\0", 1) == 0)
                ft_putstr_fd(": No such file or directory\n", 2);
            else
                ft_putstr_fd(": command not found\n", 2);
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

void exec_pipeline(t_ast_node *node, char **envp, int fd_in, t_list *pid_lst)
{
    int	pipe_fds[2];
    int	pid;
    int	err_code;
    
    if (node == NULL)
        return ;
    if (node->type == PIPE)
    {
        pipe(pipe_fds);
        pid = exec_command(node->left, fd_in, pipe_fds, envp);
        
        ft_lstadd_back(&pid_lst, ft_lstnew((void *)(&pid)));
        close(pipe_fds[1]);

        if (fd_in > 2)
            close(fd_in);
        exec_pipeline(node->right, envp, pipe_fds[0], pid_lst);
    }
    else
    {
        pipe_fds[0] = -1;
        pipe_fds[1] = STDOUT_FILENO;
        pid = exec_command(node, fd_in, pipe_fds, envp);
        ft_lstadd_back(&pid_lst, ft_lstnew((void *)(&pid)));
        if (fd_in > 2)
            close(fd_in);

        while (pid_lst)
        {
            waitpid(*((int *)(pid_lst->content)), &err_code, 0);
            if (WIFEXITED(err_code))
                g_last_exit_status = WEXITSTATUS(err_code);
            pid_lst = pid_lst->next;
        }
        ft_lstclear(&pid_lst, free);
    }
}

void execute_ast(t_ast_node *node, char **envp)
{
    t_list *pid_lst;

    pid_lst = NULL;
    pre_process_heredocs(node);
    exec_pipeline(node, envp, STDIN_FILENO, pid_lst);
    ft_free_ast(node);
    
}
