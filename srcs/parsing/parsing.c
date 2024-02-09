/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:48:01 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 18:20:48 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_split_input(char **split_input)
{
    int i;

    i = 0;
    while (split_input[i])
    {
        printf("[%s]\n", split_input[i]);
        i++;
    }
}

char **ft_split_input(char *input)
{
    char    **split_input;
    int     lenght;
    int     i;

	if (!check_quotes_closed(input))
		return (NULL);
    i = 0;
    lenght = 0;
    split_input = malloc(sizeof(char *) * 100);
    while (*input)
    {
        lenght = get_token_length(input);
        input += lenght;
        if (lenght > 0)
        {
            split_input[i] = strndup(input - lenght, lenght);
            i++;
        }
        if (*input == ' ')
            input++;
    }
    split_input[i] = NULL;
    return (split_input);
}

t_token *lexer(char *input)
{
    t_token *token_list;
    char *input_expend;
    char **split_input;
	int i;
	
	i = 0;
	token_list = NULL;
	input_expend = ft_expand_envvar(input);
	(void)input_expend;
	if (!input_expend)
		return (NULL);
	split_input = ft_split_input(input_expend);
    free(input_expend);
    if (!split_input)
		return (NULL);
	split_input = ft_clean_input(split_input);
	if (!split_input)
		return (NULL);
	token_list = tokenize(split_input);
	if (!token_list)
		return (NULL);
    while (split_input[i])
        free(split_input[i++]);
    free(split_input);
	return (token_list);
}