/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:26:01 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/04 20:15:33 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	take_the_rest(char **pre_line, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while (pre_line[0][i] != '\0' && pre_line[0][i] != '\n')
		i++;
	if (pre_line[0][i])
		i++;
	*line = ft_substr(*pre_line, 0, i);
	if (pre_line[0][i])
	{
		temp = ft_substr(*pre_line, i, (ft_strlen(*pre_line) - i));
		free(*pre_line);
		*pre_line = temp;
	}
	else
	{
		free(*pre_line);
		*pre_line = NULL;
	}
}

static char	*make_line(char *pre_line, int fd)
{
	char	*buffer;
	int		bts_read;

	bts_read = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(pre_line, '\n') && bts_read != 0)
	{
		bts_read = read(fd, buffer, BUFFER_SIZE);
		if (bts_read == 0)
			break ;
		if (bts_read == -1)
		{
			free(buffer);
			free(pre_line);
			return (NULL);
		}
		buffer[bts_read] = '\0';
		pre_line = ft_strjoin(pre_line, buffer);
		if (!pre_line)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (pre_line);
}

char	*get_next_line(int fd)
{
	static char	*pre_line[MAX_FD];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	pre_line[fd] = make_line(pre_line[fd], fd);
	if (pre_line[fd] == NULL)
		return (NULL);
	take_the_rest(&pre_line[fd], &line);
	return (line);
}
