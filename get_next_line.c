/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:04:28 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/18 00:17:41 by aquinter         ###   ########.fr       */
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

char	*clean_content(char *content_readed, int end)
{
	char	*new_content;
	
	new_content = ft_substr(content_readed, end + 1,  ft_strlen(content_readed) - (end + 1));
	free(content_readed);
	if(!new_content)
		return (NULL);
	return (new_content);
}

char	*next_reading(int fd, char *content_readed, ssize_t *bytes)
{
	char	*buffer;
	char	*new_content;

	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	// Aqui deberiamos hacer el while
	*bytes = read(fd, buffer, BUFFER_SIZE);
	if (*bytes > 0)
	{
		buffer[*bytes]= '\0';
		new_content = ft_strjoin(content_readed, buffer);
		if(!new_content)
			return (NULL);
		return (new_content);
	}
	free(buffer);
	if (*bytes == 0)
		return(content_readed);
	free(content_readed);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char 		*content_readed;
	ssize_t 			bytes;
	char				*line;
	int					end;

	if (fd < 0)
		return(NULL);
	
	content_readed = next_reading(fd, content_readed, &bytes);
	if(!content_readed)
		return(NULL);
	// if (bytes == 0 && content_readed[0] == '\0')
	// 	return(NULL);
	end = analyze_str(content_readed);
	while (end == -1 && bytes > 0)
	{
		content_readed = next_reading(fd, content_readed, &bytes);
		end = analyze_str(content_readed);
	}
	if (bytes == 0)
	{
		if(content_readed)
			return(content_readed);
		return(NULL);
	}
	line = ft_calloc(end + 2, sizeof(char));
	if (!line)
	{
		free(content_readed);
		return (NULL);
	}	
	ft_strlcpy(line, content_readed, (end + 2));
	content_readed = clean_content(content_readed, end);
	if(!content_readed)
		return (NULL);
	return (line);
}

# include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*ptr;

	fd = open("files/41_with_nl", O_RDONLY);
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