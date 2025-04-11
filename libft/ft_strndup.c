/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:22:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/11 17:22:31 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strndup(const char *s, size_t len)
{
    char    *dest;
    char    *start;
    size_t  i;

    if (s == NULL)
        return (NULL);
    dest = (char *)malloc(len + 1);
    if (dest == NULL)
        return (NULL);

    start = dest;
    for (i = 0; i < len && s[i] != '\0'; i++)
        *dest++ = s[i];
    *dest = '\0';

    return (start);
}
