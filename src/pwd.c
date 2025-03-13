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

void ft_pwd(void)
{
    char *cwd;
    const char *pwd_env;
    
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