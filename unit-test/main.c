/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:07:33 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/17 03:52:35 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#include <stdio.h>
#include <string.h>

typedef struct s_test_case {
    char *input;
    char *expected_tokens[100];
} t_test_case;

int compare_tokens(t_token *tokens, char **expected_tokens)
{
    int i = 0;
    while (expected_tokens[i] && tokens)
	{
        if (strcmp(tokens->value, expected_tokens[i]) != 0)
            return 0;
        tokens = tokens->next;
        i++;
    }
    return expected_tokens[i] == NULL && tokens == NULL;
}

void run_test(t_test_case test_tokens)
{
    t_token *tokens = lexer(test_tokens.input);
    if (compare_tokens(tokens, test_tokens.expected_tokens))
        printf("\033[0;32m[OK] \033[0m");
    else
	{
        printf("\033[0;31m[KO] {%s} \033[0m", test_tokens.input);
        // print_tokens(tokens);
    }
    free_tokens(tokens);
}

int main(void)
{
    t_test_case quoat_tests[] = {
        {"\"", {NULL}},
        {"\'", {NULL}},
        {"\"\"", {"", NULL}},
        {"''", {"", NULL}},
        {"$\"\"", {"", NULL}},
        {"$''", {"", NULL}},
        {"\"$\"", {"$", NULL}}
    };
    int num_tests_quaot = sizeof(quoat_tests) / sizeof(quoat_tests[0]);
    
    t_test_case expend_tests[] = {
        {"$lol \"$lol\" '$lol' $\"\" $'' $\"\"lol $''lol \"'lol'\" '\"lol\"' \"'\"lol\"'\" '\"'lol'\"' \"$\" '$' $? $.",
            {"mdr", "mdr", "$lol", "", "", "lol", "lol", "'lol'", "\"lol\"", "'lol'", "\"lol\"", "$", "$", "5", "$.", NULL}},
        {"$$", {"$$", NULL}},
        {"$", {"$", NULL}},
        {"\"'$lol'\"", {"'mdr'"}},
        {"test $lol test", {"test mdr test"}},
        {"'test $lol test'", {"test $lol test"}},
    };
    int num_expend_tests = sizeof(expend_tests) / sizeof(expend_tests[0]);

    printf("Testing quoat\n");
    for (int i = 0; i < num_tests_quaot; i++)
        run_test(quoat_tests[i]);
    printf("\nTesting expend\n");
    for (int i = 0; i < num_expend_tests; i++)
        run_test(expend_tests[i]);
    return 0;
}
