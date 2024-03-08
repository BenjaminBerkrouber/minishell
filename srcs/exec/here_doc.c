/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:53:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 19:26:11 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl(int fd)
{
	char	*line;
	char	*tmp;
	char	*buf;
	int		ret;

	buf = malloc(sizeof(char) * 100 + 1);
	if (!buf)
		return (NULL);
	ret = read(fd, buf, 100);
	if (ret == -1)
		return (NULL);
	buf[ret] = '\0';
	line = ft_strdup(buf);
	while (ft_strchr(line, '\n') == NULL && ret != 0)
	{
		ret = read(fd, buf, 100);
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		tmp = line;
		line = ft_strjoin(line, buf);
		free(tmp);
	}
	free(buf);
	return (line);
}

int handle_heredoc(char *delimiter, char *filename)
{
    int fd;
    int tmp_fd;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error: Failed to create temporary file for heredoc");
        exit(EXIT_FAILURE);
    }
    
    read = getline(&line, &len, stdin);
    while ((read != -1))
    {
        if (strncmp(line, delimiter, (ft_strlen(line) - 1)) == 0)
            break ;
        write(fd, line, read);
        read = getline(&line, &len, stdin);
    }
    free(line);
    close(fd);
    tmp_fd = open(filename, O_RDONLY);
    if (tmp_fd == -1)
    {
        perror("Error: Failed to open temporary file for heredoc");
        exit(EXIT_FAILURE);
    }
    return tmp_fd;
}

char *temp_file_name_from_fd(int fd)
{
    char *temp_file_name;
    
    temp_file_name = malloc(PATH_MAX);
    if (!temp_file_name)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    snprintf(temp_file_name, PATH_MAX, "/tmp/minishell_heredoc_%d", fd);
    return (temp_file_name);
}

void process_heredocs(t_ast_node *node)
{
    t_redirection *current;
    int heredoc_fd;
    char *file_name;
    static long magic_number;

    current = node->redirections;
    while (current)
    {
        if (current->type == T_HEREDOC)
        {
            magic_number += 1;
            file_name = temp_file_name_from_fd(magic_number);
            heredoc_fd = handle_heredoc(current->filename, file_name);
            free(current->filename);
            current->filename = file_name;
            close(heredoc_fd);
        }
        current = current->next;
    }
}

void pre_process_heredocs(t_ast_node *root)
{
    if (!root)
        return;

    if (root->type == CMD || root->type == HERE_DOC)
        process_heredocs(root);

    pre_process_heredocs(root->left);
    pre_process_heredocs(root->right);
}