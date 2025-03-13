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

#include "minishell.h"

//POR REVISAR TODO
void previous_pwd(void)
{
    char *oldpwd;;

    oldpwd = getenv("PWD");

    if (oldpwd)
        setenv("OLDPWD", oldpwd, 1); // Guarda el anterior PWD en PREVIOUSPWD
}

void new_pwd(char *new_path)
{
    if (!new_path) // Si la nueva ruta es NULL, obtener el directorio actual
        new_path = getcwd(NULL, 0);
    if (!new_path)// Si getcwd falla, mostrar error
    {
        perror("getcwd");
        return ;
    }
    setenv("PWD", new_path, 1);// Actualiza PWD
    free(new_path);
}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ft_pwd(void)
{
    char *cwd;
    const char *pwd_env;
    
    // Intentamos obtener el directorio de trabajo actual
    cwd = getcwd(NULL, 0); 
    
    if (!cwd)  // Si no conseguimos el directorio actual
    {
        // Intentamos obtener la variable de entorno "PWD"
        pwd_env = getenv("PWD"); 
        
        if (pwd_env)  // Si encontramos la variable PWD
        {
            printf("%s\n", pwd_env);  // Mostramos la variable PWD
        }
        else  // Si tampoco existe la variable PWD
        {
            perror("pwd");  // Mostramos el error
        }
    }
    else  // Si `getcwd` fue exitoso
    {
        printf("%s\n", cwd);  // Mostramos el directorio actual
        free(cwd);  // Liberamos la memoria asignada por getcwd
    }
}
//La función getcwd (que significa get current working directory, en español obtener el directorio de trabajo actual)
//devuelve la ruta completa del directorio de trabajo actual donde el programa está ejecutándose

//MAIN GENERADO POR CHAT GPT PARA COMPROBAR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    while (1)
    {
        printf("minishell> ");
        
        char input[1024];
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';  // Eliminar salto de línea al final

        if (strcmp(input, "exit") == 0)
            break;

        // Si el comando es "pwd"
        if (strcmp(input, "pwd") == 0)
        {
            ft_pwd();  // Llamamos a la función para mostrar el directorio actual
        }
    }

    return 0;
}