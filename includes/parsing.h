/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:48:39 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 16:56:41 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"
#include "parsing_export.h"
#include "parsing_quotes.h"


int get_token_length(char *input);

token_type determine_token_type(char *token);
void append_token(t_token **token_list, t_token *new_token);
t_token *create_token(char *value, token_type type);
int get_meta_char(char *c);
void skip_spaces(char **input);

char **split_and_or(char *input);
void    print_split_input(char **split_input);
void add_word(char **input, char ***split_input, int *i);
t_ast_node *process(char *input);
void add_token(t_token **token_list, t_token *new_token);
t_token *new_token(char *value, token_type type);

#endif