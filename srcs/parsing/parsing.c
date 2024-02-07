/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:48:01 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/07 13:11:06 by bberkrou         ###   ########.fr       */
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

t_token *tokenize(char *input)
{
	t_token *token;
    char **split_input;
    char *input_expend;

	token = malloc(sizeof(t_token));
	(void)input;
	(void)split_input;
	(void)token;
    
    input_expend = ft_expand_envvar(input);
    split_input = ft_split_input(input_expend);
	if (!split_input)
	{
		free(input_expend);
		return (NULL);
	}
	// token = get_token_type(split_input);
    // split_input = ft_clean_input(split_input);
    print_split_input(split_input);
    return (NULL);
}