/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:51:48 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 22:34:27 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **token_list, t_token *new_token)
{
	t_token	*temp;

	if (!*token_list)
		*token_list = new_token;
	else
	{
		temp = *token_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

int	is_option(char *token)
{
	int	i;

	i = 0;
	if (token && token[0] == '-')
		return (1);
	while (token[i] == '"' || token[i] == '\'')
		i++;
	if (token[i] == '-' && token[i + 1] != '\0')
	{
		if (token[i + 1] == '"' || token[i + 1] == '\'')
		{
			i += 2;
			while (token[i] && (token[i] == '"' || token[i] == '\''))
				i++;
			return (token[i] != '\0');
		}
		return (1);
	}
	return (0);
}

token_type	get_token_type(char *token, int is_first_token)
{
	if (is_first_token && !get_meta_char(token))
		return (CMD);
	else if (is_option(token))
		return (OPTION);
	else if (strcmp(token, "|") == 0)
		return (PIPE);
	else if (strcmp(token, ">") == 0)
		return (REDIRECT_OUT);
	else if (strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	else if (strcmp(token, ">>") == 0)
		return (REDIRECT_APPEND);
	else if (strcmp(token, "<<") == 0)
		return (HERE_DOC);
	else
		return (ARGUMENT);
}

int	get_token_length(char *input)
{
	int	length;
	int	in_quotes;

	length = 0;
	in_quotes = 0;
	while (*input && ((*input != ' ') || (*input == ' ' && in_quotes)))
	{
		if (*input == '\"')
			in_quotes = !in_quotes;
		input++;
		length++;
	}
	return (length);
}
