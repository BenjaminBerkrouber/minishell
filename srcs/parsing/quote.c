/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:55:49 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/16 03:42:06 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes_closed(const char *input)
{
    char quote_type;
    int i;
    
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
        return 0;
    }
    return (1);
}

void handle_char(char c, char *temp_str, int *temp_len, char *current_quote)
{
    if (c == '\'' && (*current_quote == '\0' || *current_quote == '\''))
        *current_quote = (*current_quote == '\'') ? '\0' : '\'';
    else if (c == '"' && (*current_quote == '\0' || *current_quote == '"'))
        *current_quote = (*current_quote == '"') ? '\0' : '"';
    else
        temp_str[(*temp_len)++] = c;
    temp_str[*temp_len] = '\0';
}

char *clean_quotes_from_token_value(const char *value)
{
    char temp_str[1024];
    int temp_len = 0;
    char current_quote = '\0';
    int i;
    char *cleaned_value;

    i = 0;

    while (value[i] != '\0')
    {
        handle_char(value[i], temp_str, &temp_len, &current_quote);
        i++;
    }
    cleaned_value = malloc(temp_len + 1);
    if (cleaned_value)
        strcpy(cleaned_value, temp_str);
    return (cleaned_value);
}


void clean_quotes_from_tokens(t_token *tokens) {
    while (tokens) {
        char *cleaned_value = clean_quotes_from_token_value(tokens->value);
        free(tokens->value); // Libérer l'ancienne valeur.
        tokens->value = cleaned_value; // Mettre à jour avec la nouvelle valeur nettoyée.
        tokens = tokens->next; // Passer au token suivant.
    }
}

