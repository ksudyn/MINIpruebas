/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:24 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:26 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(char **args)
{
    if (!args[1])  // Si no hay argumentos, muestra las variables de entorno
    {
        extern char **environ;
        for (int i = 0; environ[i]; i++)
            printf("%s\n", environ[i]);
    }
    else  // Si hay un argumento, establece la variable de entorno
    {
        if (putenv(args[1]) != 0)
            perror("export");
    }
}
