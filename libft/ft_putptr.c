/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:37:34 by ksudyn            #+#    #+#             */
/*   Updated: 2025/01/16 15:37:45 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	char			hex[16];
	int				i;
	int				printed_chars;

	address = (unsigned long)ptr;
	if (!address)
		return (write(1, "(nil)", 5));
	printed_chars = write(1, "0x", 2);
	i = 0;
	while (address)
	{
		hex[i++] = "0123456789abcdef"[address % 16];
		address /= 16;
	}
	while (--i >= 0)
		printed_chars += write(1, &hex[i], 1);
	return (printed_chars);
}
