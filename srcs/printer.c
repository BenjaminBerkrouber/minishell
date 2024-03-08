#include "minishell.h"

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
        fprintf(stderr, "[%s {%s}]\n", tokens->value, get_type(tokens->type));
        tokens = tokens->next;
    }
    fprintf(stderr, "\n");
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

void	print_split_input(char **split_input)
{
	int i;

	if (!split_input)
	{
		printf("NULL\n");
		return ;
	}
	i = 0;
	while (split_input[i])
	{
		printf("[%s]\n", split_input[i]);
		i++;
	}
}

char **copy_envp(char **envp)
{
	int i;
	char **new_envp;
	
	for (i = 0; envp[i] != NULL; i++);
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	for (i = 0; envp[i] != NULL; i++)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			perror("error memory");
		}
	}
	new_envp[i] = NULL;
	return (new_envp);
}