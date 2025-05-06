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

void	print_export_list(t_mini *mini)
{
	t_list	*node;
	int		printed;
	int		total;
	int		current_order;

	printed = 0;
	total = ft_lstsize_mini(mini->first_node);
	nodes_order(mini);
	current_order = 0; // Asigna el "order" a cada nodo
	while (printed < total)
	{
		node = mini->first_node;
		while (node)
		{
			if (node->order == current_order)
			{
				print_single_export(node);
				printed++;
				// Avanza al siguiente "order"
				break ;
			}
			node = node->next;
		}
		current_order++;
	}
}
// Llama a nodes_order() para asignar una "posición" alfabética a cada variable.
// Luego imprime una por una, en el orden de menor a mayor order.

int	ft_export(char **args, t_mini *mini)
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

// Si se llama sin argumentos,
// debe imprimir todas las variables de entorno en orden alfabético y con el formato:
// declare -x VAR="VAL"
// Si se llama con argumentos en formato VAR=VAL, debe:
//- Agregar la variable al entorno o modificar su valor si ya existe.
//- Validar que el nombre sea correcto
//(no puede empezar con un número o contener caracteres inválidos como = en el nombre).
// No usa export VAR sin = para marcar variables como exportadas, ya que minishell no requiere esto.
// El orden importa: cuando se imprimen las variables, deben aparecer ordenadas alfabéticamente.