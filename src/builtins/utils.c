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

void execute_builtins(t_mini *mini, char **args)
{
    if (args[0] == NULL)
        return;

    if (ft_strncmp(args[0], "cd", 3) == 0)
        ft_cd(args);
    else if (ft_strncmp(args[0], "echo", 5) == 0)
        ft_echo(args);
    else if (ft_strncmp(args[0], "env", 4) == 0)
        ft_env(args, mini);
    else if (ft_strncmp(args[0], "exit", 5) == 0)
        ft_exit(args);
    else if (ft_strncmp(args[0], "export", 7) == 0)
        ft_export(args, mini);
    else if (ft_strncmp(args[0], "pwd", 4) == 0)
        ft_pwd();
    else if (ft_strcmp(args[0], "unset") == 0)
        ft_unset(mini, args);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}
