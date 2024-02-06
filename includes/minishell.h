/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:45:18 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/06 19:00:27 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "three.h"

void libererTokens(t_token *tokens);
t_token *creerToken(char *text, t_token_type type);
t_token_type get_token_type(char *token);
t_token *tokenize(char *input);
const char *getTokenTypeName(t_token_type type);
int is_command(char *token);
int is_args(char *token);
char **ft_clean_input(char **split_input);
char *ft_expand_envvar(const char *input);
// echo $lol "$lol" '$lol' $"" $'' $""lol $''lol "'lol'" '"lol"' "'"lol"'" '"'lol'"'

#endif