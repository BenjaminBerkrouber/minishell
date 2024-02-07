/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:10:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 13:28:19 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_env_var_name(const char *name)
{
    int i;

    i = 0;
    if (!name[0] || (!isalpha(name[0]) && name[0] != '_'))
        return (0);

    while (name[i])
    {
        if (!isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }

    return (1);
}

static char *extract_var_name(const char *input, int *index)
{
    int start;
    int len = 0;
    char *var_name;
    
    if (!is_valid_env_var_name(input + *index + 1))
    {
        *index += 1;
        fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", input + *index);
        return (NULL);
    }
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

static char *get_var_value(char *var_name)
{
    char *value;
    
    value = getenv(var_name);
    if (value)
        return (value);
    return ("");
}

static void handle_quotes(const char *input, char **result, int *i, int *j, int *in_single_quote) {
    if (input[*i] == '\'' && !*in_single_quote)
    {
        *in_single_quote = 1; 
        (*result)[(*j)++] = input[(*i)++];
        while (input[*i] && input[*i] != '\'')
            (*result)[(*j)++] = input[(*i)++];
    }
    if (input[*i] == '\'' && *in_single_quote)
    {
        *in_single_quote = 0;
        (*result)[(*j)++] = input[(*i)++];
    }
}

static void handle_variable_expansion(const char *input, char **result, int *i, int *j, int in_single_quote) {
    char *var_name;
    char *value;
    
    if (input[*i] == '$' && !in_single_quote)
    {
        var_name = extract_var_name(input, i);
        if (!var_name)
            return;
        value = get_var_value(var_name);
        while (*value)
            (*result)[(*j)++] = *value++;
        free(var_name);
    }
    else {
        (*result)[(*j)++] = input[*i];
    }
    (*i)++;
}



char *ft_expand_envvar(const char *input)
{
    char *result;
    int i;
    int j;
    int in_single_quote;
    
    i = 0;
    j = 0;
    in_single_quote = 0;

    result = (char *)malloc(1024);
    if (!result)
        return (NULL);
    while (input[i])
    {
        handle_quotes(input, &result, &i, &j, &in_single_quote);
        if (input[i])
            handle_variable_expansion(input, &result, &i, &j, in_single_quote);
    }
    result[j] = '\0';
    return (result);
}
