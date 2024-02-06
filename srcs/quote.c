/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:55:49 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/06 18:13:43 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_char_to_temp_str(char c, char *temp_str, int *temp_len)
{
    temp_str[(*temp_len)++] = c;
    temp_str[*temp_len] = '\0';
}

void handle_char(char c, char *temp_str, int *temp_len, char *current_quote)
{
    if ((c == '"' || c == '\'') && (*current_quote == '\0' || *current_quote == c))
    {
        if (*current_quote == '\0')
            *current_quote = c;
        else
            *current_quote = '\0'; 
    }
    else
        if (!(*current_quote != '\0' && c == *current_quote))
            add_char_to_temp_str(c, temp_str, temp_len);
}

void process_input_str(char *input, char **cleaned, int *index_cleaned, char *temp_str, char *current_quote)
{
    int temp_len = 0;
    int i = 0;

    while (input[i] != '\0')
    {
        handle_char(input[i], temp_str, &temp_len, current_quote);
        i++;
    }

    if (*current_quote == '\0' && temp_len > 0)
    {
        cleaned[*index_cleaned] = strdup(temp_str);
        (*index_cleaned)++;
        temp_str[0] = '\0';
    }
}

char **ft_clean_input(char **split_input)
{
    char **split_clean = malloc(sizeof(char *) * 100);
    char *temp_str = malloc(sizeof(char) * 1024);
    int index_cleaned = 0;
    char current_quote = '\0';

    int i = 0;
    while (split_input[i] != NULL) {
        temp_str[0] = '\0';
        process_input_str(split_input[i], split_clean, &index_cleaned, temp_str, &current_quote);
        i++;
    }

    split_clean[index_cleaned] = NULL;
    free(temp_str);
    return split_clean;
}