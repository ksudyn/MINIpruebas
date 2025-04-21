/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:32:50 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:32:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//Esta función está diseñada para cambiar al directorio especificado por el usuario.
int cd_argument(char *path)
{
    if (chdir(path) == -1)
    {
        perror("minishell: cd");
        return 1;
    }
    
    previous_pwd();
    new_pwd(getcwd(NULL, 0));
    return 0;
}

//Esta función está diseñada para cambiar al directorio de inicio del usuario ($HOME).
int cd_home(void)
{
    char *home;
    
    home = getenv("HOME");
    if (home && chdir(home) == -1)
    {
        perror("minishell: cd");
        return 1;
    }
    
    previous_pwd();
    new_pwd(getcwd(NULL, 0));
    return 0;
}
//Chdir sirve para cambiar de carpeta (directorio) en la computadora.

//La función ft_cd es la encargada de manejar el comando cd de acuerdo a los argumentos que recibe.
void ft_cd(char **args)
{
    int i;
    
    i = 0;
    while (args[i])
        i++;

    if (i > 2)
    {
        printf("minishell: cd: too many arguments\n");
        return;
    }
    if (i == 1)
    {
        if (cd_home() != 0)
            return;
    }
    else
    {
        if (cd_argument(args[1]) != 0)
            return;
    }
    printf("se ha usado mi cd\n");
}
//Getenv busca en la libreta de la computadora y devuelve el valor de una variable de entorno.
//la busca y si existe la ejecuta
//Chdir sirve para cambiar de carpeta (directorio) en la computadora.
//getcwd(NULL, 0) Obtiene la ruta actual.
