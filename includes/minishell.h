/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:45:18 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 18:44:28 by bberkrou         ###   ########.fr       */
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

typedef enum {
    CMD,
	OPTION,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HERE_DOC,
	INFILE,
	OUTFILE,
	APPENDFILE,
	DELIMITER
} token_type;

typedef struct s_token
{
	char *value;
	token_type type;
	struct s_token *next;
} t_token;

# include "parsing.h"

t_token *lexer(char *input);
char **ft_clean_input(char **split_input);
char *ft_expand_envvar(const char *input);
t_token *tokenize(char **split_input);
// echo $lol "$lol" '$lol' $"" $'' $""lol $''lol "'lol'" '"lol"' "'"lol"'" '"'lol'"'

#endif