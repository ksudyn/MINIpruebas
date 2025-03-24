/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:45 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:47 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char    *ft_strndup(const char *s, size_t len)
{
    char    *dest;
    char    *start;
    size_t  i;

    if (s == NULL)
        return (NULL);
    dest = (char *)malloc(len + 1);
    if (dest == NULL)
        return (NULL);

    start = dest;
    for (i = 0; i < len && s[i] != '\0'; i++)
        *dest++ = s[i];
    *dest = '\0';

    return (start);
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

int	node_to_end(t_list **list, t_list *insert)
{
	t_list	*temp;

	if (!insert)
		return (-1);
	if (*list == NULL)
	{
		*list = insert;
		insert->next = NULL;
		insert->prev = NULL;
	}
	else
	{
		temp = *list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = insert;
		insert->prev = temp;
		insert->next = NULL;
	}
	return (1);
}

void	free_env(t_mini *mini)
{
	t_list	*temp;
	t_list	*next_node;

	temp = mini->env_list;
	while (temp)
	{
		next_node = temp->next;
		free(temp->variable);
		free(temp->content);
		free(temp);
		temp = next_node;
	}
	mini->env_list = NULL;
}

t_list	*env_new(char *env_var)
{
	t_list	*new_node;
	int		equal_pos;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	equal_pos = 0;
	while (env_var[equal_pos] && env_var[equal_pos] != '=')
		equal_pos++;

	new_node->variable = ft_strndup(env_var, equal_pos);
	if (env_var[equal_pos] == '=')
		new_node->content = ft_strdup(&env_var[equal_pos + 1]);
	else
		new_node->content = NULL;

	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}


void	ft_export_env(char *new_env, t_mini *mini)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = env_new(new_env);
	if (!new_node)
		return ;

	// Buscar si la variable ya existe en la lista
	temp = mini->env_list;
	while (temp)
	{
		if (strcmp(temp->variable, new_node->variable) == 0)
		{
			free(temp->content);
			temp->content = strdup(new_node->content);
			free(new_node->variable);
			free(new_node->content);
			free(new_node);
			return ;
		}
		temp = temp->next;
	}
	// Si no existe, añadirla al final de la lista
	node_to_end(&mini->env_list, new_node);
}
/*
int	ft_built_env(char **args, t_mini *mini)
{
	t_list	*temp;

	// Verifica que no se pasen argumentos a env
	if (args[1])
	{
		printf("minishell: env: Args not allowed\n");
		return (1);
	}

	temp = mini->env_list;
	while (temp)
	{
		if (temp->content) // Solo imprimimos si hay contenido
			printf("%s=%s\n", temp->variable, temp->content);
		temp = temp->next;
	}
	return (0);
}*/

int ft_built_env(char **args, t_mini *mini)
{
    t_list *temp;

    // Verifica que no se pasen argumentos a env
    if (args[1])
    {
        printf("minishell: env: Args not allowed\n");
        return (1);
    }

    temp = mini->env_list;
    while (temp)
    {
        printf("Procesando nodo: %p\n", temp);
        printf("Variable: %p, Content: %p\n", temp->variable, temp->content);

        if (temp->variable && temp->content)
        {
            printf("%s=%s\n", temp->variable, temp->content);
        }
        else
        {
            printf("Error: Invalid environment variable or content in node\n");
        }

        temp = temp->next;
    }

    return (0);
}



void	init_env(char **envp, t_mini *mini)
{
	int		i;
	t_list	*new_node;

    if (envp == NULL)
    {
        printf("Error: envp is NULL\n");
        return;
    }
	mini->env_list = NULL;
	i = 0;
	while (envp[i])
	{
        printf("Procesando envp[%d]: %s\n", i, envp[i]);
		new_node = env_new(envp[i]);
		if (!new_node)
		{
			printf("Error en '%s'\n", envp[i]);
			return ;
		}
		if (node_to_end(&mini->env_list, new_node) == -1)
        {
            printf("Error al añadir el nodo a la lista\n");
            return;
        }
		i++;
	}
    printf("todas las variables de entorno has sido procesadas y generadas\n");
}

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_env(envp, &mini);
	ft_built_env(NULL, &mini);
    printf("Llega hasta el fuincla del printf, el fallo esta fuera de estas funciones\n");
	free_env(&mini);
	return (0);
}
