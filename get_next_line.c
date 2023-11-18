/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:04:28 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/18 19:18:06 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*static_reset(char *readed)
{
	if (readed)
		free(readed);
	readed = NULL;
	return (NULL);
}

char	*build_and_clean(char **readed)
{
	char	*line;
	char	*aux;
	size_t	len;
	
	aux = ft_strchr(*readed, '\n');
	if (!aux)
		return (*readed);
	else
		len = ft_strlen(*readed) - ft_strlen(aux) + 2;
	line = malloc(len * sizeof(char));
	if (!line)
		return (static_reset(*readed));
	ft_strlcpy(line, *readed, len);
	*readed = ft_substr(*readed, len - 1, ft_strlen(aux) - 1);
	if (!*readed)
		return (NULL);
	return (line);
}

char	*next_reading(int fd, char *readed)
{
	ssize_t	bytes;
	char	*buffer;

	bytes = 1;
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (static_reset(readed));
	buffer[0] = '\0';
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		if(bytes > 0)
			readed = ft_strjoin(readed, buffer);
		if (!readed)
			return (static_reset(readed));
	}
	free(buffer);
	if (bytes == -1)
		return (static_reset(readed));
	return (readed);
}

char	*get_next_line(int fd)
{
	static char	*readed;
	char		*line;

	if (fd < 0)
		return (NULL);
	readed = next_reading(fd, readed);
	if (!readed || ft_strlen(readed) == 0)
		return (NULL);
	line = build_and_clean(&readed);
	if (!line)
		return (NULL);
	return (line);
}

# include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*ptr;

	fd = open("files/3.txt", O_RDONLY);
	if(fd == ERROR)
		return(1);
	ptr = get_next_line(fd);
	while (ptr != NULL)
	{
		printf("%s", ptr);
		free(ptr);
		ptr = get_next_line(fd);
	}
	printf("%s", ptr);
	close(fd);
	return (0);
}