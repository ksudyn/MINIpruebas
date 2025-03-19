/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:34 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:36 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int ft_unset_env(t_mini *mini, char *variable)
{
    t_env *node;
    
    node = mini->first_node;
    while (node)
    {
        if (strcmp(node->variable, variable) == 0)
        {
            if (node->prev == NULL)
                mini->first_node = node->next;
            else
                node->prev->next = node->next;

            if (node->next)
                node->next->prev = node->prev;

            free(node->variable);
            free(node->content);
            free(node);

            mini->total_nodes--;
            return (0);
        }
        node = node->next;
    }
    return (1);
}

int ft_unset(t_mini *mini, char **args)
{
    int i;
    int len;

    len = 0;
    while(args[len])
        len++;
    if(len == 1)
        return (0);
    i = 1;
    while (args[i])
    {
        if (ft_strcmp(args[i], "_") == 0 || ft_strcmp(args[i], "?") == 0)
        {
            i++;
        }
        else
        {
        ft_unset_env(mini, args[i]);
        i++;
        }
    }
    return (0);
}

//MAIN GENERADO POR CHATGPT
// Función para imprimir la lista de variables de entorno
void print_env(t_mini *mini)
{
    t_env *current = mini->first_node;
    printf("\nLista de variables de entorno:\n");
    while (current)
    {
        printf("%s=%s\n", current->variable, current->content);
        current = current->next;
    }
    printf("\n");
}

// Función para crear un nodo de entorno
t_env *create_env_node(char *var, char *value)
{
    t_env *new = malloc(sizeof(t_env));
    if (!new)
        return NULL;
    new->variable = strdup(var);
    new->content = strdup(value);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

// Función para agregar una variable al entorno (al final de la lista)
void add_env_var(t_mini *mini, char *var, char *value)
{
    t_env *new = create_env_node(var, value);
    t_env *temp = mini->first_node;

    if (!mini->first_node)
        mini->first_node = new;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
        new->prev = temp;
    }
    mini->total_nodes++;
}


// Función principal de prueba
int main(int argc, char **argv)
{
    (void)argc;
    
    // Inicializar estructura
    t_mini mini;
    mini.first_node = NULL;
    mini.total_nodes = 0;

    // Agregar variables de entorno
    add_env_var(&mini, "USER", "root");
    add_env_var(&mini, "HOME", "/home/root");
    add_env_var(&mini, "PATH", "/usr/bin:/bin");
    add_env_var(&mini, "SHELL", "/bin/bash");

    // Imprimir antes de unset
    print_env(&mini);

    // Ejecutar unset con los argumentos de entrada
    ft_unset(&mini, argv);

    // Imprimir después de unset
    print_env(&mini);

    return 0;
}