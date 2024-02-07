/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:48:39 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 13:04:53 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

char **ft_clean_input(char **split_input);
char *ft_expand_envvar(const char *input);
char *ft_expand_envvar(const char *input);
char **ft_clean_input(char **split_input);
int get_token_length(char *input);
int check_quotes_closed(const char *input);

#endif