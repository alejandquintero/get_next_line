/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:04:28 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/16 19:14:13 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# include <stdio.h>

int	analyze_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*next_reading(int fd, char *content_readed)
{
	ssize_t bytes;
	char	*buffer;
	char	*new_content;

	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes > 0)
	{
		new_content = ft_strjoin(content_readed, buffer);
		if(!new_content)
			return (NULL);
		return (new_content);
	}
	free(buffer);
	if (bytes == 0)
		return(content_readed);
	if (bytes == -1)
		return (NULL);
}

char	*get_next_line(int fd)
{
	static char 		*content_readed;
	char				*line;
	int					end;

	content_readed = next_reading(fd, content_readed);
	end = analyze_str(content_readed);
	while (end == -1)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1 || bytes == 0)
		{
			if (bytes == 0)
				return (readed);
			if (readed != NULL)
				free(readed);				
			return (NULL);
		}
		readed = ft_strjoin(readed, buffer);
		end = analyze_str(readed);
	}
	line = malloc((end + 2) * sizeof(char));
	ft_strlcpy(line, readed, (end + 2));
	readed = ft_substr(readed, end + 1,  ft_strlen(readed) - (end + 1));
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