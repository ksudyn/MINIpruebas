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

# include "../libft/libft.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

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
}   t_mini;

////...........////BUILTINS
void ft_cd(char **args);
void	init_env_list(t_mini *mini, char **envp);
void	free_env_list(t_mini *mini);
void	ft_echo(char **args);
int ft_env(char **args, t_mini *mini);
int ft_exit(char **exit_args);
int ft_export(char **args, t_mini *mini);
void ft_pwd(void);
int ft_unset(t_mini *mini, char **args);
void execute_builtins(t_mini *mini, char **args);

void ft_lstadd_back(t_list **lst, t_list *new);
int	ft_lstsize_mini(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list *ft_lstnew(void *content);


#endif
