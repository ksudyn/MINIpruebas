/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:09:26 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/22 14:09:32 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
