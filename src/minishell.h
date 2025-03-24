/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:07:42 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/11 16:54:14 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct t_list
{
    char            *variable;   // Nombre de la variable (ej. "PATH")
    char            *content;    // Valor de la variable (ej. "/usr/bin")
    int             order;       // Posición en orden alfabético
	struct t_list	*next;
	struct t_list	*prev;

}					t_list;

typedef struct s_mini
{
    t_list   *first_node;  // Apunta al primer nodo de la lista de variables de entorno
    t_list   *node_inter;        // Iterador temporal para recorrer la lista
    int     total_nodes;    // Número total de variables en la lista
    t_list   *env_list;
}   t_mini;

t_list *ft_lstlast(t_list *lst);

#endif
