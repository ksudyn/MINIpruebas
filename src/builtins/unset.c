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

#include "../minishell.h"
# include "../../libft/libft.h"

int ft_unset_env(t_mini *mini, char *variable)
{
    t_list *node;
    
    node = mini->first_node;
    while (node)
    {
        if (ft_strcmp(node->variable, variable) == 0)
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

// Función principal de prueba

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
    printf("se ha usado mi unset\n");
    return (0);
}


/*
// Función para imprimir la lista de variables de entorno
void print_env(t_mini *mini)
{
    t_list *current = mini->first_node;
    printf("\nLista de variables de entorno:\n");
    while (current)
    {
        printf("%s=%s\n", current->variable, current->content);
        current = current->next;
    }
    printf("\n");
}*/
