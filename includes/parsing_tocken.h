/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tocken.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:28:00 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 22:45:53 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOCKEN_H
# define PARSING_TOCKEN_H

# include "minishell.h"

int         check_syntax_pipe(token_type type, t_token *token_list, char **split_input, int i);
int         is_option(char *token);
void        add_token(t_token **token_list, t_token *new_token);
t_token     *new_token(char *value, token_type type);
token_type	get_token_type(char *token, int is_first_token);
void	    get_last_token_type(token_type *last_redirect_type, token_type *type);

#endif