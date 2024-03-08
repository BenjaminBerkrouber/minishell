/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:34:28 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 22:20:42 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si les guillemets dans une chaîne sont fermés.
 * 
 * @param input La chaîne à vérifier.
 * @return 1 si fermés correctement, sinon 0.
 */
int	check_quotes_closed(const char *input)
{
	char	quote_type;
	int		i;

	quote_type = '\0';
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote_type == input[i])
				quote_type = '\0';
			else if (quote_type == '\0')
				quote_type = input[i];
		}
		i++;
	}
	if (quote_type != '\0')
	{
		fprintf(stderr, "Syntaxe error : quaot %c not closed.\n", quote_type);
		g_last_exit_status = 2;
		return (0);
	}
	return (1);
}

/**
 * Ajoute ou ignore les guillemets dans une chaîne.
 * 
 * @param c Le caractère à traiter.
 * @param temp_str La chaîne temporaire où ajouter le caractère.
 * @param temp_len La longueur actuelle de temp_str.
 * @param current_quote Le type de guillemet actuellement ouvert (' ou ").
 */
void	handle_char(char c, char *temp_str, int *temp_len, char *current_quote)
{
	if (c == '\'' && (*current_quote == '\0' || *current_quote == '\''))
	{
		if (*current_quote == '\'')
			*current_quote = '\0';
		else
			*current_quote = '\'';
	}
	else if (c == '"' && (*current_quote == '\0' || *current_quote == '"'))
	{
		if (*current_quote == '"')
			*current_quote = '\0';
		else
			*current_quote = '"';
	}
	else
		temp_str[(*temp_len)++] = c;
	temp_str[*temp_len] = '\0';
}

/**
 * Supprime les guillemets d'une valeur de token.
 * 
 * @param value La valeur du token à nettoyer.
 * @return La chaîne nettoyée des guillemets.
 */
char	*clean_quotes_from_token_value(const char *value)
{
	char	*temp_str;
	int		temp_len;
	char	current_quote;
	int		i;
	char	*cleaned_value;

	i = 0;
	temp_len = 0;
	current_quote = '\0';
	temp_str = malloc(sizeof(char) * (ft_strlen(value) + 1));
	if (!temp_str)
		return (NULL);
	while (value[i] != '\0')
		handle_char(value[i++], temp_str, &temp_len, &current_quote);
	temp_str[temp_len] = '\0';
	cleaned_value = malloc(temp_len + 1);
	if (!cleaned_value)
	{
		free(temp_str);
		return (NULL);
	}
	ft_strcpy(cleaned_value, temp_str);
	free(temp_str);
	return (cleaned_value);
}

/**
 * Nettoie les guillemets de tous les tokens d'une liste.
 * 
 * @param tokens La liste des tokens à nettoyer.
 */
void	clean_quotes_from_tokens(t_token *tokens)
{
	char	*cleaned_value;

	while (tokens)
	{
		cleaned_value = clean_quotes_from_token_value(tokens->value);
		free(tokens->value);
		tokens->value = cleaned_value;
		tokens = tokens->next;
	}
}
