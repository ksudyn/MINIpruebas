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

#include "minishell.h"

void ft_exit(char **args)
{
    int status = 0;

    if (args[1])  // Si hay un argumento, convertirlo a int
        status = atoi(args[1]);

    exit(status);
}
