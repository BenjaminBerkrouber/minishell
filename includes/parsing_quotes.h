/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:55:35 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 22:21:35 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_QUOTES_H
# define PARSING_QUOTES_H

# include "minishell.h"

void    clean_quotes_from_tokens(t_token *tokens);
char    *clean_quotes_from_token_value(const char *value);
int     check_quotes_closed(const char *input);
int     is_option(char *token);

#endif