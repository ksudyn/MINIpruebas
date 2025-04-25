/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:57:50 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/15 16:57:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_mini mini;
	char *input;
    char **args;
	int i;

	(void)argc;
	(void)argv;

	mini.first_node = NULL;
	mini.total_nodes = 0;
	init_env_list(&mini, envp);

    ctrls(0);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
        {
			printf("🟡 Se ha usado Ctrl-D\n");
			break;
		}

		if (*input)
			add_history(input);

		args = ft_split(input, ' ');
		if (args && args[0])
		{
			if(is_builtin(args[0]))
				execute_builtins(&mini, args);
			else
				execute_command(&mini, args);
		}

		i = 0;
		while (args && args[i])
			free(args[i++]);
		free(args);
		free(input);
	}
	
	free_env_list(&mini);
	return 0;
}
