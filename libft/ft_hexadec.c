/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:36:15 by ksudyn            #+#    #+#             */
/*   Updated: 2025/01/16 15:36:26 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexadec(unsigned long nbr, int upper)
{
	char	*hex_digits;
	char	buffer[17];
	int		i;
	int		printed_chars;

	i = 15;
	printed_chars = 0;
	if (upper)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	while (i >= 0)
	{
		buffer[i] = hex_digits[nbr % 16];
		nbr /= 16;
		i--;
	}
	i = 0;
	while (buffer[i] == '0' && i < 15)
		i++;
	printed_chars = write(1, &buffer[i], 16 - i);
	return (printed_chars);
}
