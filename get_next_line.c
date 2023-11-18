/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:04:28 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/18 23:53:48 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*reset_readed(char **readed)
{
	free(*readed);
	*readed = NULL;
	return (NULL);
}

char	*build_and_clean(char **readed)
{
	char	*line;
	char	*aux;
	size_t	len;

	if (ft_strlen(*readed) == 0)
	{
		line = NULL;
		reset_readed(&(*readed));
	}
	else
	{
		aux = ft_strchr(*readed, '\n');
		if (!aux)
			len = ft_strlen(*readed) + 1;
		else
			len = (aux - *readed) + 2;
		line = malloc(len * sizeof(char));
		if (!line)
			return (reset_readed(&(*readed)));
		ft_strlcpy(line, *readed, len);
		if (!aux)
			reset_readed(&(*readed));
		else
		{
			*readed = ft_substr(*readed, len - 1, ft_strlen(aux) - 1);
			if (!*readed)
				return reset_readed(&(*readed));
		}
	}
	return (line);
}

char	*next_reading(int fd, char *readed)
{
	ssize_t	bytes;
	char	*buffer;

	bytes = 1;
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (reset_readed(&readed));
	buffer[0] = '\0';
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			readed = ft_strjoin(readed, buffer);
			if (!readed)
			{
				free(buffer);
				return (reset_readed(&readed));
			}
		}
	}
	free(buffer);
	if (bytes == -1)
		return (reset_readed(&readed));
	return (readed);
}

char	*get_next_line(int fd)
{
	static char	*readed;
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((readed && !ft_strchr(readed, '\n')) || !readed)
		readed = next_reading(fd, readed);
	if (!readed)
		return (NULL);
	line = build_and_clean(&readed);
	if (!line)
		return (NULL);
	return (line);
}

# include <fcntl.h>

// int	main(int argc, char *argv[])
// {
// 	int		fd;
// 	char	*ptr;
	
// 	if (argc == 1)
// 	{
// 		printf("Introduce la ruta del fichero");
// 		return (1);
// 	}
// 	fd = open(argv[1], O_RDONLY);
// 	if(fd == ERROR)
// 		return(1);
// 	ptr = get_next_line(fd);
// 	while (ptr != NULL)
// 	{
// 		printf("%s", ptr);
// 		free(ptr);
// 		ptr = get_next_line(fd);
// 	}
// 	printf("%s", ptr);
// 	close(fd);
// 	system("leaks -q a.out");
// 	return (0);
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*ptr;

// 	fd = open("files/nl", O_RDONLY);
// 	if(fd == ERROR)
// 		return(1);
// 	ptr = get_next_line(fd);
// 	while (ptr != NULL)
// 	{
// 		printf("%s", ptr);
// 		free(ptr);
// 		ptr = get_next_line(fd);
// 	}
// 	printf("%s", ptr);
// 	system("leaks -q a.out");
// 	close(fd);
// 	return (0);
// }