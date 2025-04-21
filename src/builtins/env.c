/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:45 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:47 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//INICIO DE FUNCIONES DE ENV.C

int ft_env(char **args, t_mini *mini)
{
    t_list *temp;

    // Verifica que no se pasen argumentos a env
    if (args[1])
    {
        printf("minishell: env: Args not allowed\n");
        return (1);
    }

    temp = mini->first_node;
    while (temp)
    {
        if (temp->variable && temp->content)
        {
            printf("%s=%s\n", temp->variable, temp->content);
        }
        // else
        // {
        //     printf("Error: Invalid environment variable or content in node\n");
        // }
		//lo comentado se debera quitar tras las comprobaciones
		//esto se imprimiria si hay variables sin valor, pero no debe escribir nada,
		//es mera comprobacion si funciona bien
        temp = temp->next;
    }
	printf("se ha usado mi env\n");
    return (0);
}
