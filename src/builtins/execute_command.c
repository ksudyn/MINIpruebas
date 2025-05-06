/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:34:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/16 16:34:07 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*build_env_string(t_list *node)
{
	char	*env_string;
	int		len;

	if (!node || !node->variable || !node->content)
		return (NULL);
	len = strlen(node->variable) + strlen(node->content) + 2;
	env_string = malloc(len);
	if (!env_string)
		return (NULL);
	snprintf(env_string, len, "%s=%s", node->variable, node->content);
	return (env_string);
}

char	**env_list_to_array(t_mini *mini)
{
	char	**envp;
	t_list	*current;
	int		i;

	i = 0;
	current = mini->first_node;
	envp = malloc(sizeof(char *) * (mini->total_nodes + 1));
	if (!envp)
		return (NULL);
	while (current)
	{
		envp[i] = build_env_string(current);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*ft_check_command(char **path_list, char *command)
{
	int		i;
	char	*path_temp;
	char	*path_result;

	i = -1;
	while (path_list[++i])
	{
		path_temp = ft_strjoin(path_list[i], "/");
		// el fallo del double free esta dentro de ft_strjoin,
		// como no las funciones de libft mal hechas me siguen jodiendo
		path_result = ft_strjoin(path_temp, command);
		free(path_temp);
		if (access(path_result, X_OK) == 0)
		{
			free_path_list(path_list);
			return (path_result);
		}
		free(path_result);
	}
	free_path_list(path_list);
	return (NULL);
}

char	*ft_get_path_command(char **command, t_mini *mini)
{
	t_list	*node;
	char	**path_list;
	char	*path;

	node = mini->first_node;
	if (ft_strchr(command[0], '/'))
	{
		if (access(command[0], X_OK) == 0)
			return (ft_strdup(command[0]));
		else
			return (NULL);
	}
	while (node)
	{
		if (strcmp(node->variable, "PATH") == 0)
		{
			path_list = ft_split(node->content, ':');
			path = ft_check_command(path_list, command[0]);
			return (path); // puede ser NULL o el path encontrado
		}
		node = node->next;
	}
	return (NULL);
}

void	execute_command(t_mini *mini, char **args)
{
	char	*full_path;
	char	**env_array;
	pid_t	pid;

	full_path = ft_get_path_command(args, mini);
	if (!full_path)
	{
		printf("minishell: command not found: %s\n", args[0]);
		return ;
	}
	env_array = env_list_to_array(mini);
	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, env_array);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");
	free(full_path);
	free_path_list(env_array);
}
