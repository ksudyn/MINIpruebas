/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:56 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:59 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
# include "../../libft/libft.h"

int check_long_number(char *str)
{
    unsigned long long result;
    int sign;
    int i;
    int digit;

    result = 0;
    sign = 0;
    i = 0;
    digit = 0;
    if (str[i++] == '-')
        sign = 1;
    else if (str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
			return (0);
		digit = str[i] - '0';
		if (result > LLONG_MAX / 10 || 
            (result == LLONG_MAX / 10 && digit > (LLONG_MAX % 10) + sign))
			return (0);
		result = result * 10 + digit;
        i++;
    }
    return (1);
}

int transform_number(char *str, long long *result)
{
    long long digit;
    int sign;
    int i;

    digit = 0;
    sign = 0;
    i = 0;
    if (check_long_number(str) == 0)
        return (0);
    if (str[i] == '-')
    {
        sign = 1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (str[i])
    {
        digit = digit * 10 + (str[i] - '0');
        i++;
    }
    if (digit > LLONG_MAX + sign)
            return (0);   
    *result = (long long)digit - sign;
    return (1);
}

int final_numbers(char *str, long long *result)
{
    long long number;
    int i;

    i = 0;
    if (str[i] == '\0')
        return (0);

    if (transform_number(str, &number) == 0)
        return (0);

    if(str[i] == '-')
    {
        number = number + 1;
        *result = -number;
    }
    else
        *result = number;

    return (1);
}

int multiple_args(char **exit_args, int argc)
{
    printf("se entra en multiple_args\n");
    long long exit_code;
    char *trimmed_arg;

    trimmed_arg = ft_strtrim(exit_args[1], " \f\r\n\t\v");
    if (!trimmed_arg)
        return (2);

    if (final_numbers(trimmed_arg, &exit_code) == 0)
    {
        printf("exit\n");
        printf("minishell: exit: %s: numeric argument required\n", exit_args[1]);
        free(trimmed_arg);
        return (2);
    }
    final_numbers(trimmed_arg, &exit_code);
    free(trimmed_arg);

    if (argc > 2)
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        return (-1);
    }
    return (exit_code % 256);
}

int ft_exit(char **exit_args)
{
    printf("ft_exit llamado\n");
    int i;
    int exit_status;

    i = 0;
    while (exit_args[i])
        i++;
    printf("Número de argumentos: %d\n", i);

    if (i == 1)
    {
        printf("se ha usado mi exit\n");
        exit (0);
    }
    exit_status = multiple_args(exit_args, i);
    
    if (exit_status == -1)
    {
        printf("se ha usado mi exit pero no sale por muchos argumentos\n");
        return (1);
    }
    printf("se ha usado mi exit con numeros\n");
    exit(exit_status);
}


//MAIN CREADO POR CHATGPT PARA COMPROBAR SI FUNCIONA BIEN

// Aquí van tus funciones check_long_number, transform_number, final_numbers, multiple_args, ft_exit
/*
int main(void)
{
    char input[1024];

    while (1)
    {
        printf("minishell> ");  // Muestra el prompt

        if (fgets(input, sizeof(input), stdin) == NULL) // Lee la entrada del usuario
            break;

        input[strcspn(input, "\n")] = '\0';  // Elimina el salto de línea al final

        // Dividir el input en palabras para tratar los argumentos
        char *args[10];  // Suponemos que el número máximo de argumentos es 10
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < 10)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  // Termina la lista de argumentos con NULL

        // Comprobar si el comando es "exit"
        if (strcmp(args[0], "exit") == 0)
        {
            int exit_status = multiple_args(args, i);
            if (exit_status == 0)
            {
                printf("Exiting with code 0\n");
                break;  // Salir del programa con código de salida 0
            }
            else if (exit_status == 1)
            {
                printf("Too many arguments. Not exiting.\n");
            }
            else if (exit_status == 2)
            {
                printf("Invalid argument. Exiting with error code 2.\n");
            }
            else
            {
                printf("Exiting with code %d\n", exit_status);
                break;  // Salir del programa con el código de salida calculado
            }
        }
    }

    return 0;
}
*/
