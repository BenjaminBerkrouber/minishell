/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 08:53:20 by bberkrou          #+#    #+#             */
/*   Updated: 2023/12/16 10:39:10 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *create_ast_node(t_token_type type, char *value)
{
    t_ast_node *node;
	
	node = malloc(sizeof(t_ast_node));
    if (node == NULL)
        return NULL;
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->children = NULL;
    node->children_count = 0;
    return node;
}

void add_child_node(t_ast_node *parent, t_ast_node *child)
{
	t_ast_node **new_children;
    if (parent == NULL || child == NULL)
        return;

    int new_count = parent->children_count + 1;
    new_children = realloc(parent->children, new_count * sizeof(t_ast_node *));
    if (new_children == NULL)
        return;
    new_children[parent->children_count] = child;
    parent->children = new_children;
    parent->children_count = new_count;
}

void free_ast_node(t_ast_node *node)
{
	int i;

    if (node == NULL)
	{
        return;
	}
	i = 0;
    while (i < node->children_count)
	{
        free_ast_node(node->children[i]);
		i++;
    }
    free(node->children);
    free(node->value);
    free(node);
}
