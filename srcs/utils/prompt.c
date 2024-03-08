/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:28:39 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 23:34:57 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_host(void)
{
	char	*line;
	char	**tab;
	char	*host;
	int		fd;

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
	host = strdup(tab[0]);
	ft_free_tab(tab);
	return (host);
}

char	*get_path_prompt(void)
{
	char	*pwd;
	char	*home;
	char	*path;

	pwd = getenv("PWD");
	home = getenv("HOME");
	if (!pwd || !home)
		return (NULL);
	if (strncmp(pwd, home, strlen(home)) == 0)
	{
		if (strlen(pwd) == strlen(home))
			path = strdup("~");
		else
		{
			path = malloc(sizeof(char) * (strlen(pwd) - strlen(home) + 2));
			if (!path)
				return (NULL);
			path[0] = '~';
			strcpy(path + 1, pwd + strlen(home));
		}
	}
	else
		path = strdup(pwd);
	return (path);
}

char	*build_prompt(void)
{
	char	*prompt;
	char	*user;
	char	*host;
	char	*path;

	path = get_path_prompt();
	user = get_var_value("USER");
	host = get_host();
	prompt = malloc(sizeof(char) * (ft_strlen(user) + ft_strlen(host) \
													+ ft_strlen(path) + 3 + 1));
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
