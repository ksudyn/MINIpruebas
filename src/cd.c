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

#include "minishell.h"
//POR REVISAR TODO
void update_oldpwd(void)
{
    char *oldpwd;

    oldpwd = getenv("PWD");

    if (oldpwd)
        setenv("OLDPWD", oldpwd, 1); // Guarda el anterior PWD en OLDPWD
}

void update_pwd(char *new_path)
{
    if (!new_path)
        return;
    setenv("PWD", new_path, 1); // Actualiza PWD
    free(new_path);
}

void ft_cd(char **args)
{
    char *path;
    // Contar argumentos
    int i = 0;
    while (args[i])
        i++;

    if (i > 2)
    {
        printf("minishell: cd: too many arguments\n");
        return;
    }
    if (i == 1)
        path = getenv("HOME");
    else
        path = args[1];
    // Intentar cambiar de directorio
    if (!path || chdir(path) == -1)
    {
        perror("minishell: cd");
        return;
    }
    // Si el cambio es exitoso, actualizar las variables de entorno
    update_oldpwd();
    update_pwd(getcwd(NULL, 0));
}
//Busca en la libreta de la computadora y devuelve el valor de una variable de entorno.
//la busca y si existe la ejecuta
//chdir sirve para cambiar de carpeta (directorio) en la computadora.


//main generado por chatgpt para ver funcionamienito
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
        getline(&input, &len, stdin); // Leer entrada del usuario
        input[strcspn(input, "\n")] = '\0'; // Eliminar el salto de línea

        if (strcmp(input, "exit") == 0)
            break;

        args[0] = "cd";
        args[1] = input;
        args[2] = NULL;

        ft_cd(args); // Llamar a la función cd

        // Mostrar las variables de entorno actualizadas
        printf("PWD: %s\n", getenv("PWD"));
        printf("OLDPWD: %s\n", getenv("OLDPWD"));
    }

    free(input);
    return 0;
}