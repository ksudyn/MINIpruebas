/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:00:04 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 14:58:33 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (len > i)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
