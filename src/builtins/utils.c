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

