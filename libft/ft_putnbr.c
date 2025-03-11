/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:36:52 by ksudyn            #+#    #+#             */
/*   Updated: 2025/01/16 15:37:12 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int	printed_chars;

	printed_chars = 0;
	if (n == -2147483648)
	{
		printed_chars += ft_putchar('-');
		printed_chars += ft_putchar('2');
		n = 147483648;
	}
	if (n < 0)
	{
		printed_chars += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		printed_chars += ft_putnbr(n / 10);
	}
	printed_chars += ft_putchar((n % 10) + '0');
	return (printed_chars);
}
