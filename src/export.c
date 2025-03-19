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

#include "minishell.h"



//FUNCIONES DE LA LIBFT
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
int	ft_isdigit( int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int	ft_isalnum(int c)
{
	if (ft_isalpha (c) || ft_isdigit (c))
		return (1);
	return (0);
}

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

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


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	unsigned char	*ptr;

	ptr = malloc(size * nmemb);
	if (ptr == NULL)
		return (NULL);
	total_size = 0;
	while (total_size < (size * nmemb))
	{
		ptr[total_size] = 0;
		total_size++;
	}
	return ((void *)ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

t_env *ft_lstnew(void *content)
{
    t_env *new_node;

    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->content = content;
    new_node->next = NULL;
    new_node->prev = NULL;
    return (new_node);
}

void ft_lstadd_back(t_env **lst, t_env *new)
{
    t_env *temp;

    if (!*lst || !new)
    {
        *lst = new;
        return ;
    }
    temp = ft_lstlast(*lst);
    temp->next = new;
    new->prev = temp;
}


t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}


char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	i = 0;
	dst = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dst)
		return (NULL);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

//TERMINAN FUNCIONES LIBFT

int is_valid_variable(char *var)
{
    int i;
    
    i  = 0;
    if (!var || !var[0])
        return 0;

    if (!ft_isalpha(var[0]) && var[0] != '_')
        return 0;

    while (var[i])
    {
        if (!ft_isalnum(var[i]) && var[i] != '_')
            return 0;
        i++;
    }

    return 1;  // Es válido
}
// Debe empezar con una letra o '_'
// Solo acepta letras, números y '_'

void add_or_update_variable(t_mini *mini, char *var, char *value)
{
    t_env *node;
    t_env *new_node;

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
    new_node = ft_lstnew(var);
    if (!new_node)
        return;
    // Agregar el nuevo nodo al final de la lista
    ft_lstadd_back(&mini->first_node, new_node);
}

void nodes_order(t_mini *mini)
{
    t_env   *node;
    t_env   *next_node;
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
    t_env *node;

    nodes_order(mini);  // Primero ordenamos la lista alfabéticamente

    node = mini->first_node;
    while (node)
    {
        // Omite las variables con solo un carácter igual a '_'
        if (ft_strlen(node->variable) == 1 && node->variable[0] == '_')
        {
            node = node->next;  // Omite las variables con solo un carácter que sea _
            continue;
        }
        // Imprime el formato "declare -x VAR="VALUE""
        if (node->content)
            printf("declare -x %s=\"%s\"\n", node->variable, node->content);
        else
            printf("declare -x %s\n", node->variable);

        node = node->next;
    }
}

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
        if (is_valid_variable(var_name))
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
        mini->total_nodes = ft_lstsize(mini->first_node);
        nodes_order(mini);
        print_export_list(mini);
        return (0);
    }
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


//UN MAIN CREADO CON CHATGPT PATA VER SI FUNCIONA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Inicializar un entorno de pruebas
    t_mini mini;
    mini.first_node = NULL;
    mini.total_nodes = 0;

    // Agregar algunas variables de entorno iniciales
    add_or_update_variable(&mini, "USER", "alice");
    add_or_update_variable(&mini, "HOME", "/home/alice");
    add_or_update_variable(&mini, "SHELL", "/bin/bash");

    // Comprobar el comportamiento de `ft_export` sin argumentos
    printf("=== Sin argumentos ===\n");
    char *args1[] = {"export", NULL};  // No pasa argumentos, solo el comando
    ft_export(args1, &mini);  // Debería imprimir las variables ordenadas alfabéticamente

    // Agregar más variables de entorno
    add_or_update_variable(&mini, "PATH", "/usr/bin:/bin");
    add_or_update_variable(&mini, "EDITOR", "vim");

    // Comprobar el comportamiento de `ft_export` con una asignación de variable
    printf("\n=== Con argumentos ===\n");
    char *args2[] = {"export", "NEW_VAR=value", NULL};  // Agregar una nueva variable
    ft_export(args2, &mini);  // Debería agregar `NEW_VAR` con su valor a la lista

    // Comprobar el comportamiento de `ft_export` con una actualización de variable
    printf("\n=== Actualizar variable ===\n");
    char *args3[] = {"export", "HOME=/home/alice/updated", NULL};  // Actualizar `HOME`
    ft_export(args3, &mini);  // Debería actualizar el valor de `HOME`

    // Imprimir la lista final de variables
    printf("\n=== Lista Final ===\n");
    ft_export(args1, &mini);  // Debería imprimir todas las variables ordenadas correctamente

    return 0;
}
