/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:23:12 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 22:12:25 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_char_to_result(t_expansion_params *params, char c)
{
	char	*tmp;
	char	*value;

	value = malloc(sizeof(char) * 2);
	value[0] = c;
	value[1] = 0;
	tmp = (*params->result);
	(*params->result) = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	(*params->i)++;
}

/**
 * Gère le changement d'état lorsqu'un caractère de citation est rencontré
 * dans une chaîne d'entrée lors de l'expansion des variables.
 *
 * @param c Le caractère actuellement traité.
 * @param in_single_quote Un pointeur vers l'état actuel de citation,
 *                        mis à jour en fonction du caractère c.
 */
void	handle_quotes(const char c, int *in_single_quote)
{
	if (c == '\'' && *in_single_quote == 0)
		*in_single_quote = 1;
	else if (c == '\'' && *in_single_quote == 1)
		*in_single_quote = 0;
	else if (c == '"' && *in_single_quote == 0)
		*in_single_quote = 2;
	else if (c == '"' && *in_single_quote == 2)
		*in_single_quote = 0;
}

char	*quote_value_if_needed(const char *value)
{
	char	*quoted_value;
	int		i;
	int		j;

	quoted_value = malloc(strlen(value) * 2 + 1);
	if (!quoted_value)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (is_meta_char(value[i]))
		{
			quoted_value[j++] = '\"';
			quoted_value[j++] = value[i++];
			quoted_value[j++] = '\"';
		}
		else
		{
			quoted_value[j++] = value[i++];
		}
	}
	quoted_value[j] = '\0';
	return (quoted_value);
}

/**
 * Expande le code de sortie stocké dans `g_last_exit_status` en une chaîne,
 * et l'ajoute au résultat de l'expansion.
 *
 * @param params La structure contenant les paramètres d'expansion,
 *               y compris le buffer de résultat et les indices de parcours.
 */
void	expand_exit_status(t_expansion_params *params)
{
	char	*exit_status_str;
	char	*tmp;

	exit_status_str = ft_itoa(g_last_exit_status);
	if (!exit_status_str)
		return ;
	tmp = (*params->result);
	(*params->result) = ft_strjoin(tmp, exit_status_str);
	free(tmp);
	free(exit_status_str);
	*params->i += 2;
}
