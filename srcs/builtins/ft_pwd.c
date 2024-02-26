/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:27:42 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/20 20:13:18 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int pars_args(char **argv)
{
	if (!argv || !*argv)
		return (0);
	while (*argv)
	{
		if (*argv[0] == '-')
		{
			fprintf(stderr, "env: invalid option -- '%s'\nTry 'env --help'\
				for more information.\n", *argv++);
			return (125);
		}
		else
		{
			fprintf(stderr, "env: ‘%s’: No such file or directory\n", *argv++);
			return (127);
		}
	}
	return (0);
}

int ft_pwd(char **args, char **envp)
{
	char *path;
	int exit_status;
	
	if (!envp && !*envp)
	{
		perror("Error NULL");
		return (1);	
	}
	if (args)
		args++;
	exit_status = pars_args(args);
	if (exit_status != 0)
		return (exit_status);
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("Error\n");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}