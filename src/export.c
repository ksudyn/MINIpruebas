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

typedef struct s_env
{
    char            *variable;   // Nombre de la variable (ej. "PATH")
    char            *content;    // Valor de la variable (ej. "/usr/bin")
    int             order;       // Posición en orden alfabético
    struct s_env    *next;       // Siguiente nodo en la lista
}   t_env;


typedef struct s_mini
{
    t_env   *first_node;  // Apunta al primer nodo de la lista de variables de entorno
    t_env   *node_inter;        // Iterador temporal para recorrer la lista
    int     total_nodes;    // Número total de variables en la lista
}   t_mini;

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

int	ft_lstsize(t_node *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		lst = lst->next;
		cnt++;
	}
	return (cnt);
}

t_env	*ft_new_node(char *var, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->variable = ft_strdup(var);
	node->content = value ? ft_strdup(value) : NULL;
	node->order = 0;  // Se actualizará luego en `create_nodes_order`
	node->next = NULL;
	return (node);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
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

int	ft_lstsize(t_node *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		lst = lst->next;
		cnt++;
	}
	return (cnt);
}
//TERMINAN FUNCIONES LIBFT

int is_valid_variable(char *var)
{
    int i;
    
    i  = 0;
    if (!var || !var[0])
        return 0;

    if (!isalpha(var[0]) && var[0] != '_')
        return 0;

    while (var[i])
    {
        if (!isalnum(var[i]) && var[i] != '_')
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
    new_node = ft_new_node(var, value);
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

int ft_export(char **args, t_mini *mini)
{
    int exit_status = 0;

    // Si no hay argumentos, solo se deben imprimir las variables de entorno
    if (!args[1])  // Es lo mismo que argc == 1 pero más simple
    {
        // Contamos los nodos (variables de entorno)
        mini->total_nodes = ft_lstsize(mini->first_node);
        
        // Ordenamos las variables alfabéticamente
        create_nodes_order(mini);

        // Imprimimos las variables de entorno
        print_export_list(mini);
        
        return exit_status;
    }
    else
    {
        // Si hay argumentos, procesamos cada uno
        export_args(args, mini, &exit_status);
    }

    return exit_status;
}

int ft_export(char **args, t_mini *mini)
{
    int exit_status;
                char *var_name;
            char *value;
            int i;

    exit_status = 0;
    if (!args[1]) 
    {
        mini->total_nodes = ft_lstsize(mini->first_node);
        nodes_order(mini);
        print_export_list(mini);
        return exit_status;
    }
    else
    {
        i = 1;
        while (args[i])
        {
            var_name = ft_strdup(args[i]);
            value = ft_strchr(var_name, '=');  // Busca el '=' que separa la variable del valor
            if (value)
            {
                *value = '\0';  // Separamos el nombre de la variable y el valor
                value++;  // El valor empieza justo después del '='
            }
            if (is_valid_variable(var_name))
            {
                add_or_update_variable(mini, var_name, value);
            }
            else
            {
                // Si no es válida, mostramos un mensaje de error
                ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", var_name);
                exit_status = 1;  // Establecemos el estado de error
            }
            free(var_name);
            i++;
        }
    }

    return exit_status;
}

void export_args(char **args, t_mini *mini, int *exit_status)
{
    int i;
    char *var_name;
    char *value;

    i = 1; // Empezamos desde el segundo argumento (el primero es "export")
    *exit_status = 0; // Establecemos el valor inicial del exit_status
    while (args[i])
    {     // Separamos el argumento en nombre de la variable y su valor
        var_name = ft_strdup(args[i]);
        value = ft_strchr(var_name, '=');
        if (value)
        {
            *value = '\0';  // Separamos el nombre de la variable y su valor
            value++;  // El valor empieza justo después del signo '='
        }
        // Verificar si el nombre de la variable es válido
        if (is_valid_variable(var_name))
        {
            // Agregar o actualizar la variable en la lista
            add_or_update_variable(mini, var_name, value);
        }
        else
        {
            // Si no es válido, mostrar un mensaje de error
            ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", var_name);
            *exit_status = 1; // Establecemos un estado de error
        }  // Liberamos la memoria de la variable que usamos para almacenar el nombre
        free(var_name);
        i++;
    }
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