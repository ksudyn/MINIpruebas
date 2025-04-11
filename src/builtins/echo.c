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

#include "../minishell.h"
# include "../../libft/libft.h"

/*
void	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		new_line = 0;
		i++;
	}

	while(args[i])
	{
		printf("%s", args[i]);
		if(args[i + 1])
			printf(" ");
		i++;
	}

	if(new_line == 1)
		printf("\n");
}*/

int	is_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		new_line = 0;
		i++;
	}

	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}

	if (new_line)
		printf("\n");
}
/*
int main(int argc, char **argv)
{
	if(argc > 1)
		ft_echo(argv);
	else
		printf("\n");

	return 0;
}
*/