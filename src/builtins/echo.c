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

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	built_echo(char **args)
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
}

int main(int argc, char **argv)
{
	if(argc > 1)
		built_echo(argv);
	else
		printf("\n");

	return 0;
}
