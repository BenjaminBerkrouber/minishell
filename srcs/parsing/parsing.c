/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:40:54 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/12 13:39:55 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Ajoute un mot à la liste de chaînes splittées, en gérant les guillemets pour
 * considérer les séquences entre guillemets comme un seul mot.
 *
 * @param input			Pointeur vers la chaîne d'entrée actuellement analysée.
 * @param split_input	Adresse de la liste de chaînes splittées à 
 * 							laquelle ajouter le mot.
 * @param i				Index dans la liste de chaînes où 
 * 							ajouter le nouveau mot.
 */
void	add_word(char **input, char ***split_input, int *i)
{
	int		j;
	char	quote;

	j = 0;
	quote = '\0';
	while ((*input)[j] && (((*input)[j] != ' ' && (*input)[j] != '<'
		&& (*input)[j] != '>' && (*input)[j] != '|') || quote))
	{
		if ((*input)[j] == '\'' || (*input)[j] == '"')
		{
			if (quote == (*input)[j])
				quote = '\0';
			else if (quote == '\0')
				quote = (*input)[j];
			j++;
		}
		else
			j++;
	}
	if (j > 0)
	{
		(*split_input)[*i] = strndup(*input, j);
		*input += j;
		(*i)++;
	}
}

/**
 * Ajoute un opérateur de redirection à la liste de chaînes splittées, gérant
 * les opérateurs simples et doubles comme "<", ">", ">>", et "<<".
 *
 * @param input			Pointeur vers la chaîne d'entrée actuellement analysée.
 * @param split_input	Adresse de la liste de chaînes splittées à laquelle 
 * 							ajouter l'opérateur.
 * @param i				Index dans la liste de chaînes où ajouter
 * 							le nouvel opérateur.
 */
void	add_redirection_operator(char **input, char ***split_input, int *i)
{
	if (**input == '<' || **input == '>')
	{
		if ((*(*input + 1) == '<' && **input == '<')
			|| (*(*input + 1) == '>' && **input == '>'))
		{
			(*split_input)[*i] = strndup(*input, 2);
			*input += 2;
		}
		else
		{
			(*split_input)[*i] = strndup(*input, 1);
			*input += 1;
		}
		(*i)++;
	}
}

/**
 * Ajoute un opérateur de pipe ou de logique ET à la liste de chaînes 
 * splittées, gérant les opérateurs simples et doubles comme "|", "||", et "&&".
 *
 * @param input			Pointeur vers la chaîne d'entrée actuellement analysée.
 * @param split_input	Adresse de la liste de chaînes splittées à 
 * 							laquelle ajouter l'opérateur.
 * @param i				Index dans la liste de chaînes où ajouter 
 * 							le nouvel opérateur.
 */
void	add_pipe_or_and_operator(char **input, char ***split_input, int *i)
{
	if (**input == '|')
	{
		if (*(*input + 1) == '|')
		{
			(*split_input)[*i] = strndup(*input, 2);
			*input += 2;
		}
		else
		{
			(*split_input)[*i] = strndup(*input, 1);
			*input += 1;
		}
		(*i)++;
	}
	else if (**input == '&')
	{
		if (*(*input + 1) == '&')
		{
			(*split_input)[*i] = strndup(*input, 2);
			*input += 2;
		}
		(*i)++;
	}
}

/**
 * Divise la chaîne d'entrée en une liste de sous-chaînes basée sur des espaces
 * et des opérateurs de redirection et logiques, tout en gérant les guillemets.
 *
 * @param input La chaîne d'entrée à diviser.
 * @return Un tableau de sous-chaînes résultant de la division de l'entrée.
 */
char	**ft_split_input(char *input)
{
	char	**split_input;
	int		i;

	i = 0;
	split_input = malloc(sizeof(char *) * (ft_strlen(input) * 2));
	if (!split_input)
		return (NULL);
	while (*input)
	{
		skip_spaces(&input);
		add_word(&input, &split_input, &i);
		add_pipe_or_and_operator(&input, &split_input, &i);
		add_redirection_operator(&input, &split_input, &i);
		skip_spaces(&input);
	}
	split_input[i] = NULL;
	return (split_input);
}

/**
 * Analyse la chaîne d'entrée, étend les variables d'environnement,
 * divise en sous-chaînes, et génère une liste de tokens représentant
 * les éléments de commande.
 *
 * @param input		La chaîne d'entrée contenant la commande à analyser.
 * 
 * @return La liste de tokens générée à partir de la chaîne d'entrée.
 */
t_token	*lexer(char *input)
{
	t_token	*token_list;
	char	*input_expend;
	char	**split_input;
	int		i;

	i = 0;
	token_list = NULL;
	if (!check_quotes_closed(input))
		return (NULL);
	input_expend = ft_expand_envvar(input);
	if (!input_expend)
		return (NULL);
	split_input = ft_split_input(input_expend);
	free(input_expend);
	if (!split_input)
		return (NULL);
	token_list = tokenize(split_input);
	while (split_input[i])
		free(split_input[i++]);
	free(split_input);
	clean_quotes_from_tokens(token_list);
	if (!token_list)
		return (NULL);
	return (token_list);
}
