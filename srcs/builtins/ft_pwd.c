/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:27:42 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/17 05:45:46 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
	char *path;
	
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