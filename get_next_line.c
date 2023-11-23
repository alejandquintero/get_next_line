/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:04:28 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/23 22:29:02 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*reset_readed(char **readed)
{
	if (*readed)
		free(*readed);
	*readed = NULL;
	return (NULL);
}

int	clean(char **readed, size_t len, char *new_line_ptr)
{
	char	*aux;

	if (!new_line_ptr)
		reset_readed(&(*readed));
	else
	{
		aux = *readed;
		*readed = ft_substr(*readed, len - 1, ft_strlen(new_line_ptr) - 1);
		free(aux);
		if (!*readed)
			return (-1);
		else if (ft_strlen(*readed) == 0)
			reset_readed(&(*readed));
	}
	return (1);
}

char	*build(char **readed)
{
	char	*line;
	char	*aux;
	int		res;
	size_t	len;

	aux = ft_strchr(*readed, '\n');
	if (!aux)
		len = ft_strlen(*readed) + 1;
	else
		len = (aux - *readed) + 2;
	line = malloc(len * sizeof(char));
	if (!line)
		return (reset_readed(&(*readed)));
	ft_strlcpy(line, *readed, len);
	res = clean(readed, len, aux);
	if (res == -1)
	{
		free (line);
		return (reset_readed(&(*readed)));
	}
	return (line);
}

char	*next_reading(int fd, char *readed, char *buffer)
{
	ssize_t	bytes;
	char	*aux;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			aux = readed;
			readed = ft_strjoin(readed, buffer);
			free(aux);
			if (!readed)
				return (reset_readed(&readed));
		}
	}
	if (bytes == -1)
		return (reset_readed(&readed));
	return (readed);
}

char	*get_next_line(int fd)
{
	static char	*readed;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((readed && !ft_strchr(readed, '\n')) || !readed)
	{
		buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
		if (!buffer)
			return (reset_readed(&readed));
		buffer[0] = '\0';
		readed = next_reading(fd, readed, buffer);
		free(buffer);
	}
	if (!readed)
		return (NULL);
	line = build(&readed);
	if (!line)
		return (NULL);
	return (line);
}
