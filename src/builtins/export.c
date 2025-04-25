/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:24 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:26 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_or_update_variable(t_mini *mini, char *var, char *value)
{
    t_list *node;
    t_list *new_node;

    node = mini->first_node;
    // Buscar si la variable ya existe en la lista
    while (node != NULL)
    {
        if (ft_strcmp(node->variable, var) == 0)
        {
            // Si la variable existe, actualizamos su valor
            free(node->content);  // Liberar el valor anterior
            if (value)
                node->content = ft_strdup(value);
            else
                node->content = NULL;
            return;
        }
        node = node->next;
    }
    // Si la variable no existe, crear un nuevo nodo
    new_node = new_node_export(var, value);//cambio de funciones
    if (!new_node)
        return;
    // Agregar el nuevo nodo al final de la lista
    node_to_end(&mini->first_node, new_node);//cambio de funciones
}

void nodes_order(t_mini *mini)
{
    t_list   *node;
    t_list   *next_node;
    int     order;

    node = mini->first_node;
    while (node != NULL)
    {
        order = 0;
        next_node = mini->first_node;
        while (next_node)
        {
            if (ft_strcmp(node->variable, next_node->variable) > 0)
                order++;
            next_node = next_node->next;
        }
        node->order = order;
        node = node->next;
    }
}

void print_export_list(t_mini *mini)
{
    t_list *node;
    int printed = 0;
    int total = ft_lstsize_mini(mini->first_node);
    int current_order = 0;

    nodes_order(mini); // Asigna el "order" a cada nodo

    while (printed < total)
    {
        node = mini->first_node;
        while (node)
        {
            if (node->order == current_order)
            {
                // Ignora la variable "_"
                if (!(ft_strlen(node->variable) == 1 && node->variable[0] == '_'))
                {
                    if (node->content)
                        printf("declare -x %s=\"%s\"\n", node->variable, node->content);
                    else
                        printf("declare -x %s\n", node->variable);
                }
                printed++;
                break; // Avanza al siguiente "order"
            }
            node = node->next;
        }
        current_order++;
    }
}
//Llama a nodes_order() para asignar una "posición" alfabética a cada variable.
//Luego imprime una por una, en el orden de menor a mayor order.

int export_args(char **args, t_mini *mini)
{
    int i;
    int exit_status;
    char *var_name;
    char *value;

    i = 0;
    exit_status = 0;
    while (args[++i])
    {
        var_name = ft_strdup(args[i]);
        if (!var_name)
            return (1);
        value = ft_strchr(var_name, '=');
        if (value)
            *value++ = '\0';
        if (is_valid_variable_export(var_name))
            add_or_update_variable(mini, var_name, value);
        else
        {
            printf("minishell: export: `%s': not a valid identifier\n", var_name);
            exit_status = 1;
        }
        free(var_name);
    }
    return (exit_status);
}

int ft_export(char **args, t_mini *mini)
{
    if (!args[1])
    {
        mini->total_nodes = ft_lstsize_mini(mini->first_node);
        nodes_order(mini);
        print_export_list(mini);
        return (0);
    }
    printf("se ha usado mi export\n");
    return (export_args(args, mini));
}

//Si se llama sin argumentos,
//debe imprimir todas las variables de entorno en orden alfabético y con el formato:
//declare -x VAR="VAL"
//Si se llama con argumentos en formato VAR=VAL, debe:
//- Agregar la variable al entorno o modificar su valor si ya existe.
//- Validar que el nombre sea correcto
//(no puede empezar con un número o contener caracteres inválidos como = en el nombre).
//No usa export VAR sin = para marcar variables como exportadas, ya que minishell no requiere esto.
//El orden importa: cuando se imprimen las variables, deben aparecer ordenadas alfabéticamente.
