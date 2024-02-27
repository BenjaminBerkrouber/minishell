/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:30:51 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/27 17:13:46 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection_type ft_type_to_redirection(token_type token)
{
    t_redirection_type type;
    
    if (token == REDIRECT_IN)
        type = T_REDIRECT_IN;
    else if (token == REDIRECT_OUT)
        type = T_REDIRECT_OUT;
    else if (token == HERE_DOC)
        type = T_HEREDOC;
    else if (token == REDIRECT_APPEND)
        type = T_APPEND;
    else
        type = T_REDIRECT_NONE;
    return (type);
}

t_redirection	*ft_redirectionlast(t_redirection *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_redirection	*ft_redirection_new(char *filename, t_redirection_type type)
{
	t_redirection	*element;

	element = malloc(sizeof(t_redirection));
	if (!element)
		return (NULL);
	element->filename = filename;
	element->type = type;
	element->next = NULL;
	return (element);
}

void ft_redirectionadd_back(t_redirection **redirection_lst, t_redirection *new)
{
    t_redirection	*last;

	if (!new || !redirection_lst)
		return ;
	if (*redirection_lst == NULL)
		(*redirection_lst) = new;
	else
	{
		last = ft_redirectionlast(*redirection_lst);
		last->next = new;
	}
}
