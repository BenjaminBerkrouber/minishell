/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:46:01 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/17 06:43:55 by bberkrou         ###   ########.fr       */
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

int ft_env(char **argv, char **envp)
{
	int	exit_status;
	
	if (!envp && !*envp)
	{
		perror("Error NULL");
		return (1);	
	}
	if (argv)
		argv++;
	exit_status = pars_args(argv);
	if (exit_status != 0)
		return (exit_status);
	while (*envp)
		printf("%s\n", *envp++);
	return (0);
}