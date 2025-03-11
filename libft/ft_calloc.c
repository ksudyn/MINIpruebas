/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:21:27 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 14:47:26 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	unsigned char	*ptr;

	ptr = malloc(size * nmemb);
	if (ptr == NULL)
		return (NULL);
	total_size = 0;
	while (total_size < (size * nmemb))
	{
		ptr[total_size] = 0;
		total_size++;
	}
	return ((void *)ptr);
}
