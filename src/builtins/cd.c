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
# include "../../libft/libft.h"
//LAS UTILIZAN  PWD SE USAN EN LAS FUNCIONES CD, LUEGO SE USARA EL .H Y SE PODRAN QUITAR CUNADO TODO ESTE JUNTO
void previous_pwd(void)
{
    char *oldpwd;;

    oldpwd = getenv("PWD");

    if (oldpwd)
        setenv("OLDPWD", oldpwd, 1); // Guarda el anterior PWD en PREVIOUSPWD
}
//Getenv busca en la libreta de la computadora y devuelve el valor de una variable de entorno.
//la busca y si existe la ejecuta

void new_pwd(char *new_path)
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

//FUNCIONES QUE FT_CD USARA, LUEGO SE MODIFICARAN EN BASE AL TYPEDEF STRUCT

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

/*
//main generado por chatgpt para ver funcionamien//POR REVISAR TODO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char *input = NULL;
    size_t len = 0;
    char *args[3];

    while (1)
    {
        printf("minishell> ");
        getline(&input, &len, stdin);  // Leer entrada del usuario
        input[strcspn(input, "\n")] = '\0';  // Eliminar el salto de línea

        if (strcmp(input, "exit") == 0)
            break;

        args[0] = "cd";
        args[1] = input;
        args[2] = NULL;

        ft_cd(args);  // Llamar a la función cd

        // Mostrar las variables de entorno actualizadas
        printf("PWD: %s\n", getenv("PWD"));
        printf("OLDPWD: %s\n", getenv("OLDPWD"));
    }

    free(input);
    return 0;
}*/