/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:45:48 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 22:57:57 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_pipe(token_type type, t_token *lst, char **split_input, int i)
{
	if (is_token_redirection(type) || type == PIPE)
	{
		fprintf(stderr, "bash: erreur de syntaxe près");
		fprintf(stderr, " du symbole inattend « %s »\n", split_input[i]);
		g_last_exit_status = 2;
		free_tokens(lst);
		return (1);
	}
	return (0);
}

void	get_last_token_type(token_type *last_redirect_type, token_type *type)
{
	if (*last_redirect_type == REDIRECT_IN)
		*type = INFILE;
	else if (*last_redirect_type == REDIRECT_OUT)
		*type = OUTFILE;
	else if (*last_redirect_type == REDIRECT_APPEND)
		*type = APPENDFILE;
	else if (*last_redirect_type == HERE_DOC)
		*type = DELIMITER;
	*last_redirect_type = CMD;
}

t_token	*tokenize(char **split_input)
{
	int			i;
	int			is_first_token;
	token_type	last_redirect_type;
	t_token		*token_list;
	token_type	type;

	i = 0;
	is_first_token = 1;
	last_redirect_type = CMD;
	token_list = NULL;
	while (split_input[i])
	{
		type = get_token_type(split_input[i], is_first_token);
		if (is_token_redirection(last_redirect_type))
		{
			if (check_syntax_pipe(type, token_list, split_input, i))
				return (NULL);
			get_last_token_type(&last_redirect_type, &type);
		}
		else if (is_token_redirection(type))
			last_redirect_type = type;
		add_token(&token_list, new_token(split_input[i++], type));
		is_first_token = (type == PIPE);
	}
	return (token_list);
}
