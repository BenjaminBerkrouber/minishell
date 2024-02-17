/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 06:14:20 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/17 06:45:04 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(char *env_var, char ***envp)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(env_var);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], env_var, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			while ((*envp)[i + 1])
			{
				(*envp)[i] = (*envp)[i + 1];
				i++;
			}
			(*envp)[i] = NULL;
			break;
		}
		i++;
	}
}

int	ft_unset(char **args, char **envp)
{
	if (!args || !*args)
		return (0);
	args++;
	while (*args)
	{
		ft_unsetenv(*args, &envp);
		args++;
	}
	return (0);
}
