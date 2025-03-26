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

//FUNCIONES DE LIBFT

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	result = (char *)malloc((end - start + 2) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (start <= end)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}
//FIN FUNCIONES LIBFT

int check_long_number(char *str)
{
    unsigned long long result = 0;
    int sign = 0;
    int i = 0;
    int digit = 0;

    if (str[i] == '-')
    {
        sign = 1;
        i++;
    }
    else if (str[i] == '+')
        i++;

    while (str[i])
    {
        if (!isdigit(str[i]))
			return (0);
		digit = str[i] - '0';
		if (result > LLONG_MAX / 10
			|| (result == LLONG_MAX / 10 && digit > (LLONG_MAX % 10) + sign))
			return (0);
		result = result * 10 + digit;
		i++;
    }
    return (1);
}

int transform_number(char *str, long long *result)
{
    unsigned long long digit = 0;
    int sign = 0;
    int i = 0;

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
        *result = (long long)digit;
    return (1);
}


//por rvisar 


int final_numbers(char *str)
{
    long long number;

    if (*str == '\0')
        return (0);

    if (transform_number(str, &number) == 0)
        return (0);

    return (1);
}

int multiple_args(char **exit_args, int argc)
{
    long long exit_code;
    char *trimmed_arg;

    trimmed_arg = ft_strtrim(exit_args[1], " \f\r\n\t\v");
    if (!trimmed_arg)
        return (2); // Error en la asignación de memoria

    if (final_numbers(trimmed_arg) == 0)
    {
        printf("exit\n");
        printf("minishell: exit: %s: numeric argument required\n", exit_args[1]);
        free(trimmed_arg);
        return (2);
    }
    final_number(trimmed_arg, &exit_code);
    free(trimmed_arg);

    if (argc > 2)
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        return (-1); // Indica que no se debe salir
    }

    return (exit_code % 256);
}

int exit(char **exit_args)
{
    int i = 0;
    int exit_status;

    while (exit_args[i])
        i++;

    if (i == 1)
        exit(0); // Si no hay argumentos, salir con código 0

    exit_status = multiple_args(exit_args, i);
    
    if (exit_status == -1)
        return (1); // No se sale del shell si hay "too many arguments"

    exit(exit_status);
}

