/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:48:39 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/15 23:17:47 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

typedef struct s_expansion_params
{
    char **result;
    int *i;
    int *j;
    int *in_single_quote;
} t_expansion_params;


void clean_quotes_from_tokens(t_token *tokens);
char *ft_expand_envvar(const char *input);
int get_token_length(char *input);
int check_quotes_closed(const char *input);

token_type determine_token_type(char *token);
void append_token(t_token **token_list, t_token *new_token);
t_token *create_token(char *value, token_type type);
int is_meta_char(char *str);
void skip_spaces(char **input);

#endif