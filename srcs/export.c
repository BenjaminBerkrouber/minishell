#include "minishell.h"

static char *extract_var_name(const char *input, int *index) {
    int start = *index + 1; // Commence après le symbole $
    int len = 0;
    while (input[start + len] && (isalnum(input[start + len]) || input[start + len] == '_')) {
        len++;
    }
    char *var_name = (char *)malloc(len + 1);
    if (!var_name)
        return (NULL); // Gestion d'erreur simplifiée
    strncpy(var_name, input + start, len);
    var_name[len] = '\0';
    *index = start + len; // Met à jour l'indice pour pointer après le nom de la variable
    return var_name;
}

static char *get_var_value(char *var_name) {
    char *value = getenv(var_name);
    return value ? value : ""; // Utilise une chaîne vide si la variable n'est pas définie
}

char *ft_expand_envvar(const char *input) {
    char *result = (char *)malloc(strlen(input) * 2 + 1); // Alloue de l'espace pour le résultat
    if (!result)
        return (NULL);

    int i = 0, j = 0;
    int in_single_quote = 0; // Indique si nous sommes à l'intérieur de guillemets simples

    while (input[i]) {
        if (input[i] == '\'' && !in_single_quote) {
            in_single_quote = 1; // Entre dans une séquence de guillemets simples
            result[j++] = input[i++];
            while (input[i] && input[i] != '\'') {
                result[j++] = input[i++]; // Copie littéralement tout jusqu'au prochain guillemet simple
            }
        }

        if (input[i] == '\'' && in_single_quote) {
            in_single_quote = 0; // Termine la séquence de guillemets simples
            result[j++] = input[i++];
            continue;
        }

        if (input[i] == '$' && !in_single_quote) { // N'étend que si nous ne sommes pas à l'intérieur de guillemets simples
            char *var_name = extract_var_name(input, &i);
            char *value = get_var_value(var_name);
            while (*value) {
                result[j++] = *value++;
            }
            free(var_name);
        } else {
            result[j++] = input[i++];
        }
    }
    result[j] = '\0'; // Termine la chaîne de résultat
    return result;
}
