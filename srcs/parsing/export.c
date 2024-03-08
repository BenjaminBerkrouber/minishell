/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:47:35 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 15:21:56 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status = 18;

/**
 * Extrait le nom d'une variable d'environnement à partir d'une chaîne d'entrée.
 *
 * @param input La chaîne d'entrée contenant le nom de la variable.
 * @param index Un pointeur vers l'indice actuel dans la chaîne d'entrée.
 *              Cet indice est mis à jour pour pointer après le nom extrait.
 *
 * @return Le nom de la variable d'environnement extrait.
 */
char	*extract_var_name(const char *input, int *index)
{
	int		start;
	int		len;
	char	*var_name;

	len = 0;
	start = *index + 1;
	while (input[start + len]
		&& (isalnum(input[start + len]) || input[start + len] == '_'))
		len++;
	var_name = (char *)malloc(len + 1);
	if (!var_name)
		return (NULL);
	strncpy(var_name, input + start, len);
	var_name[len] = '\0';
	*index = start + len;
	return (var_name);
}

/**
 * Récupère la valeur d'une variable d'environnement donnée.
 * 
 * @param var_name 	Le nom de la variable d'environnement dont on souhaite 
 * 					obtenir la valeur.
 * 
 * @return 			La valeur de la variable d'environnement si elle existe, 
 * 					sinon une chaîne vide.
 */
char	*get_var_value(char *var_name)
{
	char	*value;
	char	*quoted_value;

	value = getenv(var_name);
	if (!value)
		return (strdup(""));
	quoted_value = quote_value_if_needed(value);
	return (quoted_value);
}

/**
 * Expande la valeur d'une variable d'environnement donnée en la recherchant
 * par son nom, puis ajoute cette valeur au résultat de l'expansion.
 *
 * @param input 	La chaîne d'entrée à partir de laquelle le nom de 
 * 					la variable est extrait.
 * @param params 	La structure contenant les paramètres d'expansion,
 *				 	y compris le buffer de résultat et 
 *					les indices de parcours.
 */
static void	expand_env_variable(const char *input, t_expansion_params *params)
{
	char	*var_name;
	char	*value;

	var_name = extract_var_name(input, params->i);
	if (!var_name)
		return ;
	value = get_var_value(var_name);
	while (*value)
	{
		(*params->result)[(*params->j)++] = *value++;
	}
	free(var_name);
}

/**
 * Traite l'expansion des variables d'environnement dans une chaîne d'entrée,
 * en appelant les fonctions appropriées pour gérer l'expansion de 
 * chaque variable.
 *
 * @param input 	La chaîne d'entrée contenant les variables 
 * 					d'environnement à expandre.
 * @param params 	La structure contenant les paramètres d'expansion,
 *					y compris le buffer de résultat et les indices de parcours.
 */
void	handle_variable_expansion(const char *input, t_expansion_params *params)
{
	if (input[*params->i] == '$' && *params->in_single_quote != 1)
	{
		if (input[*params->i + 1] == '?')
			expand_exit_status(params);
		else if ((input[*params->i + 1] == '"' || input[*params->i + 1] == '\'')
			&& *params->in_single_quote == 0)
			expand_env_variable(input, params);
		else if (!ft_isalpha(input[*params->i + 1]))
		{
			add_char_to_result(params, input[*params->i]);
			if (input[*params->i] == '$')
				add_char_to_result(params, input[*params->i]);
		}
		else if (input[*params->i + 1] != ' ' && input[*params->i + 1] != '\0'
			&& *params->in_single_quote != 1)
			expand_env_variable(input, params);
		else
		{
			add_char_to_result(params, input[*params->i]);
			if (input[*params->i] == '$')
				*params->i += 1;
		}
	}
	else
		add_char_to_result(params, input[*params->i]);
}

/**
 * Parcourt une chaîne d'entrée pour expandre toutes les variables 
 * d'environnement qu'elle contient, y compris 
 * le code de sortie spécial `$?`.
 *
 * @param input		La chaîne d'entrée à traiter pour l'expansion 
 * 					des variables.
 *
 * @return 			Une nouvelle chaîne contenant le résultat de 
 * 					l'expansion des variables.
 */
char	*ft_expand_envvar(const char *input)
{
	char				*result;
	int					i;
	int					j;
	int					in_single_quote;
	t_expansion_params	params;

	result = malloc(sizeof(char) * 1024);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quote = 0;
	params.result = &result;
	params.i = &i;
	params.j = &j;
	params.in_single_quote = &in_single_quote;
	while (input[i])
	{
		handle_quotes(input[i], &in_single_quote);
		if (input[i])
			handle_variable_expansion(input, &params);
	}
	result[j] = '\0';
	return (result);
}
