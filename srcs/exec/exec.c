/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:52:08 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/26 20:43:04 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_debog(char **split_input)
{
	int i;

	if (!split_input)
	{
		printf("NULL\n");
		return ;
	}
	i = 0;
	while (split_input[i])
	{
		printf("[%s] ", split_input[i]);
		i++;
	}
    printf("\n");
}

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
    args = malloc(sizeof(char *) * i + 1);
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


static int exec_command(t_ast_node *node, int in_fd, int out_fd, char **envp)
{
    pid_t pid;
    char *path;
    char **args;

    pid = fork();
    if (pid == 0)
    {
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
        execve(path, args, envp);
        exit(EXIT_FAILURE);
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
        // node left executre and ft[1]
        pid = exec_command(node->left, fd_in, pipe_fds[1], envp);
        close(pipe_fds[1]);
        if (fd_in > 2)
            close(fd_in);

        // node right execut and ft[0]
        exec_pipeline(node->right, envp, pipe_fds[0]);
        close(pipe_fds[0]);
        waitpid(pid, &err_code, 0);
    }
    else
    {
        exec_command(node, fd_in, STDOUT_FILENO, envp);
        if (fd_in > 2)
            close(fd_in);
    }
}

void execute_ast(t_ast_node *node, char **envp)
{
    exec_pipeline(node, envp, STDIN_FILENO);
}
