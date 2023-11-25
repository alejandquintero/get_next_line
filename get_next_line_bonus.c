/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:55:24 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/25 17:21:00 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*reset_cache(char **cache)
{
	if (*cache)
		free(*cache);
	*cache = NULL;
	return (NULL);
}

int	clean_cache(char **cache, size_t len, char *nl_ptr)
{
	char	*aux;

	if (!nl_ptr)
		reset_cache(&(*cache));
	else
	{
		aux = *cache;
		*cache = ft_substr(*cache, len - 1, ft_strlen(nl_ptr) - 1);
		free(aux);
		if (!*cache)
			return (ERROR);
		else if (ft_strlen(*cache) == 0)
			reset_cache(&(*cache));
	}
	return (SUCCESS);
}

char	*build_line(char **cache)
{
	char	*line;
	char	*nl_ptr;
	int		result;
	size_t	len;

	nl_ptr = ft_strchr(*cache, '\n');
	if (!nl_ptr)
		len = ft_strlen(*cache) + 1;
	else
		len = (nl_ptr - *cache) + 2;
	line = malloc(len * sizeof(char));
	if (!line)
		return (reset_cache(&(*cache)));
	ft_strlcpy(line, *cache, len);
	result = clean_cache(cache, len, nl_ptr);
	if (result == ERROR)
	{
		free (line);
		return (reset_cache(&(*cache)));
	}
	return (line);
}

char	*read_next_line(int fd, char *cache, char *buffer)
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
			aux = cache;
			cache = ft_strjoin(cache, buffer);
			free(aux);
			if (!cache)
				return (reset_cache(&cache));
		}
	}
	if (bytes == ERROR)
		return (reset_cache(&cache));
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache[OPEN_MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((cache[fd] && !ft_strchr(cache[fd], '\n')) || !cache[fd])
	{
		buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
		if (!buffer)
			return (reset_cache(&cache[fd]));
		buffer[0] = '\0';
		cache[fd] = read_next_line(fd, cache[fd], buffer);
		free(buffer);
		if (!cache[fd])
			return (NULL);
	}
	line = build_line(&cache[fd]);
	if (!line)
		return (NULL);
	return (line);
}
