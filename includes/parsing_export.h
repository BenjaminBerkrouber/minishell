/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:44:08 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 15:19:14 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_EXPORT_H
# define PARSING_EXPORT_H

# define EXPAND_STATUS 1
# define EXPAND_VARIABLE 2
# define NO_EXPANSION 0
# define ADD_CHARACTER 3
# define ADVANCE_POINTER 4


typedef struct s_expansion_params
{
    char **result;
    int *i;
    int *j;
    int *in_single_quote;
} t_expansion_params;

char	*ft_expand_envvar(const char *input);

int		is_meta_char(char c);
void	add_char_to_result(t_expansion_params *params, char c);
char	*extract_var_name(const char *input, int *index);
void	handle_quotes(const char c, int *in_single_quote);
char	*quote_value_if_needed(const char *value);
void	expand_exit_status(t_expansion_params *params);
#endif