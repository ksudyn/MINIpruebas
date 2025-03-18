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
/*
void ft_unset(char **args)
{
    if (args[1])
        unsetenv(args[1]);  // Elimina la variable de entorno
}*/

void ft_unset_env_node(t_mini *mini, char *variable)
{
    t_env *current = mini->first_node;

    while (current)
    {
        if (strcmp(current->variable, variable) == 0)
        {
            // Si el nodo a eliminar es el primero
            if (current->prev == NULL)
                mini->first_node = current->next;
            else
                current->prev->next = current->next;

            // Si el nodo a eliminar es el último
            if (current->next)
                current->next->prev = current->prev;

            // Libera la memoria del nodo
            free(current->variable);
            free(current->content);
            free(current);

            mini->total_nodes--;
            return;
        }
        current = current->next;
    }
}

void ft_unset_env(t_mini *mini, char **args)
{
    int i;
    
    i = 1; // Comenzamos desde 1 porque el primer argumento es el comando "unset"
    while (args[i])
    {
        // Omitir variables especiales
        if (ft_strcmp(args[i], "_") == 0 || ft_strcmp(args[i], "?") == 0)
        {
            i++;
            continue;
        }

        // Llamar a la función de eliminación del nodo (que ya has implementado)
        ft_unset_env_node(mini, args[i]);

        i++;
    }
}


// 🔹 Función de prueba
int main() {
    // 🌱 Crear lista de variables de entorno
    t_env *env_list = new_env_var("USER", "root", 1);
    env_list->next = new_env_var("HOME", "/home/root", 2);
    env_list->next->next = new_env_var("PATH", "/bin:/usr/bin", 3);

    // 🛠 Simulamos `unset HOME`
    char *args[] = {"unset", "HOME", NULL};
    ft_built_unset(args, &env_list);

    // 📌 Imprimir el entorno actualizado
    t_env *tmp = env_list;
    while (tmp) {
        printf("%s=%s\n", tmp->variable, tmp->content);
        tmp = tmp->next;
    }

    // 🔥 Liberar memoria final
    while (env_list) {
        t_env *next = env_list->next;
        free(env_list->variable);
        free(env_list->content);
        free(env_list);
        env_list = next;
    }

    return 0;
}
