/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:23:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/04 20:08:08 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_spaces(char **input)
{
    while (**input && **input == ' ')
        (*input)++;
}

int get_meta_char(char *c)
{
    if (strncmp(c, "|", 1) == 0)
        return PIPE;
    if (strncmp(c, "<", 1) == 0)
        return REDIRECT_IN;
    if (strncmp(c, ">", 1) == 0)
        return REDIRECT_OUT;
    if (strncmp(c, ">>", 2) == 0)
        return REDIRECT_APPEND;
    if (strncmp(c, "<<", 2) == 0)
        return HERE_DOC;
    return 0;
}

char *get_type(int type)
{
    switch (type)
    {
    case CMD:
        return "CMD";
    case OPTION:
        return "OPTION";
    case ARGUMENT:
        return "ARGUMENT";
    case PIPE:
        return "PIPE";
    case REDIRECT_IN:
        return "REDIRECT_IN";
    case REDIRECT_OUT:
        return "REDIRECT_OUT";
    case REDIRECT_APPEND:
        return "REDIRECT_APPEND";
    case HERE_DOC:
        return "HERE_DOC";
    case INFILE:
        return "INFILE";
    case OUTFILE:
        return "OUTFILE";
    case APPENDFILE:
        return "APPENDFILE";
    case DELIMITER:
        return "DELIMITER";
    default:
        return "UNKNOWN";
    }
}

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        printf("[%s {%s}]\n", tokens->value, get_type(tokens->type));
        tokens = tokens->next;
    }
    printf("\n");
}

void    free_tokens(t_token *tokens)
{
    t_token *tmp;

    if (!tokens)
        return ;
    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}

void print_ast(t_ast_node *node, int level)
{
    t_token *tokens;
    if (node == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("    ");

    if (!node || !node->token)
        return ;
    tokens = node->token;
    if (node->redirections)
        printf("DEBOG filename : |%s| type = |%d|\n", node->redirections->filename, node->redirections->type);
    if (node->redirections && node->redirections->next)
        printf("DEBOG filname : |%s|\n", node->redirections->next->filename);   
    while (tokens)
    {
        printf("{%s}[%s] ", get_type(tokens->type), tokens->value);
        tokens = tokens->next;
    }
    printf("\n");
    if (node->left != NULL) {
        print_ast(node->left, level + 1);
    }
    if (node->right != NULL) {
        print_ast(node->right, level + 1);
    }
}

int is_token_redirection(token_type token)
{
    return ( token == REDIRECT_IN ||
        token == REDIRECT_OUT ||
        token == REDIRECT_APPEND ||
        token == HERE_DOC);
}

int is_token_file(token_type token)
{
    return ( token == INFILE ||
        token == OUTFILE ||
        token == APPENDFILE ||
        token == DELIMITER);
}

void set_syntax_error(const char *message, const char *value)
{
    if (value)
        fprintf(stderr, "bash: erreur de syntaxe près du symbole inattendu « %s »\n", value);
    else
        fprintf(stderr, "%s\n", message);
    g_last_exit_status = 2;
}

int syntaxer(t_token *tokens)
{
    t_token *current = tokens;

    if (!current)
    {
        set_syntax_error("erreur de syntaxe près du symbole inattendu « newline »", NULL);
        return 0;
    }
    if (current->type == PIPE)
    {
        set_syntax_error("erreur de syntaxe près du symbole inattendu", "|");
        return 0;
    }

    while (current)
    {
        if (is_token_redirection(current->type) && (!current->next || is_token_redirection(current->next->type) || current->next->type == PIPE))
        {
            set_syntax_error("erreur de syntaxe près du symbole inattendu", current->next ? current->next->value : "newline");
            return 0;
        }
        if (current->type == PIPE && (!current->next || current->next->type == PIPE))
        {
            set_syntax_error("syntax error near unexpected token", current->next ? "`|'" : "newline");
            return 0;
        }
        current = current->next;
    }

    return 1;
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
