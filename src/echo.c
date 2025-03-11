/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:54:32 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/11 17:15:27 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if(args[1] == -n)
	{
		new_line = 0;
		i++;
	}

	while(args[i])
	{
		printf("%s", args[i]);
		if(srgs[i + 1])
			printf(" ");
		i++;
	}

	if(new_line = 1)
		printf("\n");
}

int main(int argc, char **argv)
{
	builtin_echo(argv);
	return 0;
}
