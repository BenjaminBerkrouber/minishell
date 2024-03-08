/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:43:24 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/09 00:29:05 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_syntax_error(const char *message, const char *value)
{
	if (value)
	{
		fprintf(stderr, "bash: erreur de syntaxe près du symbole");
		fprintf(stderr, " inattendu « %s »\n", value);
	}
	else
		fprintf(stderr, "%s\n", message);
	g_last_exit_status = 2;
}

int	pross_syntaxer(t_token *c)
{
	if (is_token_redirection(c->type)
		&& (!c->next || is_token_redirection(c->next->type)
			|| c->next->type == PIPE))
	{
		if (c->next)
			set_syntax_error("erreur de syntaxe près du \
				symbole inattendu", c->next->value);
		else
			set_syntax_error("erreur de syntaxe près du \
				symbole inattendu", "newline");
		return (0);
	}
	if (c->type == PIPE
		&& (!c->next || c->next->type == PIPE))
	{
		if (c->next)
			set_syntax_error("syntax error near unexpected token", "`|'");
		else
			set_syntax_error("syntax error near unexpected token", "newline");
		return (0);
	}
	return (1);
}

int	syntaxer(t_token *tokens)
{
	t_token	*c;

	c = tokens;
	if (!c)
		set_syntax_error("erreur de syntaxe près du symbole inattendu \
			« newline »", NULL);
	else if (c->type == PIPE)
		set_syntax_error("erreur de syntaxe près du symbole inattendu", "|");
	if (!c || c->type == PIPE)
		return (0);
	while (c)
	{
		if (!pross_syntaxer(c))
			return (0);
		c = c->next;
	}
	return (1);
}
