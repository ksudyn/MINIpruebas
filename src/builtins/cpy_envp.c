/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:06:02 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/10 17:06:03 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
# include "../../libft/libft.h"

// Función para crear un nodo de entorno

t_list	*create_env_node(char *var, char *value)
{
	t_list	*new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->variable = strdup(var);
	new->content = strdup(value);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// Función para agregar una variable al entorno (al final de la lista)
void	add_env_var(t_mini *mini, char *var, char *value)
{
	t_list	*new = create_env_node(var, value);
	t_list	*temp;

	temp = mini->first_node;
	if (!new)
		return ;
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


void	init_env_list(t_mini *mini, char **envp)
{
	int		i = 0;
	char	*equal;
	char	*key;
	char	*value;

	while (envp[i])
	{
		equal = strchr(envp[i], '=');
		if (equal)
		{
			key = strndup(envp[i], equal - envp[i]);
			value = strdup(equal + 1);
			add_env_var(mini, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}


void	free_env_list(t_mini *mini)
{
	t_list	*current = mini->first_node;
	t_list	*tmp;

	while (current)
	{
		tmp = current->next;
		free(current->variable);
		free(current->content);
		free(current);
		current = tmp;
	}
	mini->first_node = NULL;
	mini->total_nodes = 0;
}//esta libera la memoria del envp que tú has creado y almacenado en tu estructura t_mini,
//cuando cierras tu minishell o ya no necesitas esa copia


// int	main(int argc, char **argv, char **envp)
// {
// 	t_mini mini;

// 	(void)argc;
// 	(void)argv;
// 	mini.first_node = NULL;
// 	mini.total_nodes = 0;

// 	init_env_list(&mini, envp);

//     printf("🌱 Entorno copiado:\n");
// 	// Aquí puedes usar mini.first_node para export, env, unset, etc.

// 	free_env_list(&mini);
// 	return (0);
// }