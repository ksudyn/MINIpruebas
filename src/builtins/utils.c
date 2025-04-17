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
# include "../../libft/libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *temp;

    if (!*lst || !new)
    {
        *lst = new;
        return ;
    }
    temp = ft_lstlast(*lst);
    temp->next = new;
    new->prev = temp;
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

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_list *ft_lstnew(void *content)
{
    t_list *new_node;

    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return (NULL);
    new_node->content = content;
    new_node->next = NULL;
    new_node->prev = NULL;
    return (new_node);
}

t_list	*new_doble_node(char *token)
{
	t_list	*new_node;

	new_node = malloc(1 * sizeof(t_list));
	if (!new_node)
		return (free(token), NULL);
	new_node->cmd_arg = NULL;
	new_node->cmd_name = NULL;
	new_node->cmd_path = NULL;
	new_node->content = ft_strtrim(token, " \t\v\n\r\b\f");
	if (!new_node->content)
		return (free(new_node), free(token), NULL);
	return (new_node->next = NULL, new_node->prev = NULL, new_node);
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

/*
int main(int argc, char **argv, char **envp)
{
    t_mini mini;
    mini.first_node = NULL;
    mini.total_nodes = 0;

    char *args[] = {"env", NULL};  // Un ejemplo de argumento para probar el comando "env"
    (void)argc;
    (void)argv;

    // Inicializar la lista de entorno a partir del envp del sistema
    init_env_list(&mini, envp);
    
    // Probar la ejecución de un builtin (como 'env')
    execute_builtins(&mini, args);
    // Liberar memoria antes de finalizar el programa
    free_env_list(&mini);

    return 0;
}*/

