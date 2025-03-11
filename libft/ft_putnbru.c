/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:38:52 by ksudyn            #+#    #+#             */
/*   Updated: 2025/01/16 15:39:19 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbru(unsigned int nbr)
{
	int	printed_chars;

	printed_chars = 0;
	if (nbr > 9)
		printed_chars += ft_putnbru(nbr / 10);
	ft_putchar((nbr % 10) + '0');
	printed_chars++;
	return (printed_chars);
}
