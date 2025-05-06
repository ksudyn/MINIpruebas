/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:06 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:10 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	previous_pwd(void)
{
	char	*oldpwd;

	;
	oldpwd = getenv("PWD");
	if (oldpwd)
		setenv("OLDPWD", oldpwd, 1);
}
// Getenv busca en la libreta de la computadora y devuelve el valor de una variable de entorno.
// la busca y si existe la ejecuta

void	new_pwd(char *new_path)
{
	if (!new_path)
		new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd");
		return ;
	}
	setenv("PWD", new_path, 1);
	free(new_path);
}

void	ft_pwd(void)
{
	char		*cwd;
	const char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pwd_env = getenv("PWD");
		if (pwd_env)
		{
			printf("%s\n", pwd_env);
		}
		else
		{
			perror("pwd");
		}
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	printf("se ha usado mi pwd\n");
}
// La función getcwd (que significa get current working directory, en español obtener el directorio de trabajo actual)
// devuelve la ruta completa del directorio de trabajo actual donde el programa está ejecutándose
