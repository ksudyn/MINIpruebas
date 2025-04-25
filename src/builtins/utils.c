/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:53:45 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/24 15:53:47 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_path_list(char **path_list)
{
	int	i;

	i = 0;
	if (!path_list)
		return ;
	while (path_list[i])
	{
		free(path_list[i]);
		i++;
	}
	free(path_list);
}

int	ft_lstsize_mini(t_list *lst)
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

t_list	*new_node_export(char *var, char *value)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->cmd_arg = NULL;
	new_node->cmd_name = NULL;
	new_node->cmd_path = NULL;
	new_node->variable = ft_strdup(var);
	new_node->content = value ? ft_strdup(value) : NULL;
	new_node->order = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
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
		insert->next = NULL;
		insert->prev = temp;
	}
	return (1);
}

int is_valid_variable_export(char *var)
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