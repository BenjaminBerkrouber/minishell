/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:10:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/17 04:44:01 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int last_exit_status = 5;

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
    char *quoted_value;
    size_t total_length;

    value = getenv(var_name);
    if (!value)
        return (ft_strdup(""));
    total_length = strlen(value) + 3;
    quoted_value = malloc(total_length);
    if (!quoted_value)
        return (NULL);
    quoted_value[0] = '\"';
    quoted_value[1] = '\0';
    ft_strlcat(quoted_value, value, total_length - 1);
    ft_strlcat(quoted_value, "\"", total_length);
    return (quoted_value);
}


static void handle_quotes(const char *input, t_expansion_params *params)
{
    if (input[*params->i] == '\'' && *params->in_single_quote == 0)
    {
        *params->in_single_quote = 1; 
        (*params->result)[(*params->j)++] = input[(*params->i)++];
        while (input[*params->i] && input[*params->i] != '\'')
            (*params->result)[(*params->j)++] = input[(*params->i)++];
    }
    if (input[*params->i] == '\'' && *params->in_single_quote == 1)
    {
        *params->in_single_quote = 0;
        (*params->result)[(*params->j)++] = input[(*params->i)++];
    }
    if (input[*params->i] == '"' && *params->in_single_quote == 0)
    {
        *params->in_single_quote = 2;
        (*params->result)[(*params->j)++] = input[(*params->i)++];
    }
    if (input[*params->i] == '"' && *params->in_single_quote == 2)
    {
        *params->in_single_quote = 0;
        (*params->result)[(*params->j)++] = input[(*params->i)++];
    }
}

static void expand_exit_status(t_expansion_params *params)
{
    char    *exit_status_str;
    char    *value;

    exit_status_str = ft_itoa(last_exit_status);
    if (!exit_status_str)
        return;
    value = exit_status_str;
    while (*value)
    {
        (*params->result)[(*params->j)++] = *value++;
    }
    free(exit_status_str);

    *params->i += 2; 
}

static void expand_env_variable(const char *input, t_expansion_params *params)
{
    char    *var_name;
    char    *value;

    var_name = extract_var_name(input, params->i);
    if (!var_name)
        return;
    value = get_var_value(var_name);
    while (*value)
    {
        (*params->result)[(*params->j)++] = *value++;
    }
    free(var_name);
}

static void add_char_to_result(t_expansion_params *params, char c)
{
    (*params->result)[(*params->j)++] = c;
    (*params->i)++;
}

static void handle_variable_expansion(const char *input, t_expansion_params *params)
{
    if (input[*params->i] == '$' && *params->in_single_quote != 1)
    {
        if (input[*params->i + 1] == '?')
            expand_exit_status(params);
        else if ((input[*params->i + 1] == '"' || input[*params->i + 1] == '\'') && *params->in_single_quote == 0)
            expand_env_variable(input, params);
        else if (!ft_isalnum(input[*params->i + 1]))
            add_char_to_result(params, input[*params->i]);            
        else if (input[*params->i + 1] != ' ' && input[*params->i + 1] != '\0')
            expand_env_variable(input, params);
        else
            add_char_to_result(params, input[*params->i]);
    }
    else
    {
        add_char_to_result(params, input[*params->i]);
    }
}

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

