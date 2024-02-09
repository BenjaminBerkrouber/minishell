/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:10:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 18:57:08 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extrait le nom de la variable d'environnement depuis une chaîne d'entrée à partir d'un indice donné.
 * 
 * @param input La chaîne d'entrée contenant la variable d'environnement à extraire.
 * @param index Un pointeur vers l'indice dans la chaîne d'entrée où commence le nom de la variable.
 * 
 * @return Le nom de la variable d'environnement extrait, alloué dynamiquement.
 *         Retourne NULL si l'allocation échoue ou si le nom de la variable est invalide.
 *         L'indice est mis à jour pour pointer après la fin du nom de la variable extraite.
 */
static char *extract_var_name(const char *input, int *index)
{
    int start;
    int len = 0;
    char *var_name;
    
    len = 0;
    start = *index + 1;
    while (input[start + len] && (isalnum(input[start + len]) || input[start + len] == '_'))
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
 * @param var_name Le nom de la variable d'environnement dont on souhaite obtenir la valeur.
 * 
 * @return La valeur de la variable d'environnement si elle existe, sinon une chaîne vide.
 */
static char *get_var_value(char *var_name)
{
    char *value;
    
    value = getenv(var_name);
    if (value)
        return (value);
    return ("");
}

/**
 * Traite les séquences de guillemets simples dans une chaîne d'entrée et copie le contenu entre guillemets dans le résultat.
 * 
 * @param input La chaîne d'entrée à analyser pour les guillemets.
 * @param params Structure contenant les paramètres nécessaires pour le traitement, 
 *               y compris le résultat en cours de construction, les indices actuels de traitement, 
 *               et un indicateur pour le statut des guillemets simples.
 * 
 * Note: Cette fonction met à jour les indices et le statut des guillemets dans `params`.
 */
static void handle_quotes(const char *input, t_expansion_params *params)
{
    if (input[*params->i] == '\'' && !*params->in_single_quote)
    {
        *params->in_single_quote = 1; 
        (*params->result)[(*params->j)++] = input[(*params->i)++];
        while (input[*params->i] && input[*params->i] != '\'')
            (*params->result)[(*params->j)++] = input[(*params->i)++];
    }
    if (input[*params->i] == '\'' && *params->in_single_quote)
    {
        *params->in_single_quote = 0;
        (*params->result)[(*params->j)++] = input[(*params->i)++];
    }
}

/**
 * Traite l'expansion des variables d'environnement dans une chaîne d'entrée, en remplaçant les noms de variables par leurs valeurs.
 * 
 * @param input La chaîne d'entrée contenant potentiellement des variables d'environnement à expandre.
 * @param params Structure contenant les paramètres nécessaires pour l'expansion, 
 *               incluant le résultat en cours de construction, les indices de traitement actuels, 
 *               et un indicateur pour le statut des guillemets simples.
 * 
 * Note: Les variables à l'intérieur des guillemets simples ne sont pas expansées. 
 * Cette fonction met à jour les indices de traitement et construit le résultat final dans `params`.
 */
static void handle_variable_expansion(const char *input, t_expansion_params *params)
{
    char *var_name;
    char *value;
    
    if (input[*params->i] == '$' && !*params->in_single_quote)
    {
        var_name = extract_var_name(input, params->i);
        if (!var_name)
            return;
        value = get_var_value(var_name);
        while (*value)
            (*params->result)[(*params->j)++] = *value++;
        free(var_name);
    }
    else
    {
        (*params->result)[(*params->j)++] = input[*params->i];
        (*params->i)++;
    }
}

/**
 * Effectue l'expansion des variables d'environnement dans une chaîne d'entrée.
 * 
 * @param input La chaîne d'entrée où l'expansion des variables d'environnement doit être effectuée.
 * 
 * @return Une nouvelle chaîne avec les variables d'environnement expansées. 
 * La chaîne est allouée dynamiquement et doit être libérée par l'appelant.
 * Retourne NULL en cas d'échec d'allocation.
 * 
 * Note: Cette fonction gère également les guillemets simples pour s'assurer que les variables
 * à l'intérieur des guillemets ne sont pas expansées.
 */
char *ft_expand_envvar(const char *input)
{
    char *result = (char *)malloc(1024);
    int i = 0, j = 0, in_single_quote = 0;
    t_expansion_params params = {&result, &i, &j, &in_single_quote};

    if (!result)
        return (NULL);

    while (input[i])
    {
        handle_quotes(input, &params);
        if (input[i])
            handle_variable_expansion(input, &params);
    }
    result[j] = '\0';
    return (result);
}

