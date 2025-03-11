/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:24:05 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 15:43:58 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **result, size_t fail_pos)
{
	size_t		i;

	if (fail_pos > 0)
	{
		i = fail_pos - 1;
		while (i > 0)
		{
			free (result[i--]);
		}
		free(result[0]);
	}
	free(result);
	return (NULL);
}

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*get_next_word(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (ft_substr(s, 0, len));
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	words;
	char	**result;

	if (!s)
		return (NULL);
	i = 0;
	words = count_words(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s && i < words)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			result[i++] = get_next_word(s, c);
			if (!result [i - 1])
				return (ft_free(result, i - 1));
		}
		while (*s && *s != c)
			s++;
	}
	return (result[i] = NULL, result);
}
