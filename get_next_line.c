/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:04:28 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/15 21:26:21 by aquinter         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char 		*readed;
	char		*aux;
	char		*line;
	char		buffer[BUFFER_SIZE];
	int			end;
	ssize_t		bytes;

	printf("antes-- %s \n", readed);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == -1 || bytes == 0)
		return (NULL);
	readed = ft_strdup(buffer);
	end = analyze_str(readed);	
	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (end == -1)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1 || bytes == 0)
		{
			printf("%s", readed);
			if (aux != NULL)
				free(aux);
			if (bytes == 0)
				return (readed);
			if (readed != NULL)
				free(readed);				
			return (NULL);
		}
		aux = ft_strdup((const char *)readed);
		if (readed != NULL)
			free(readed);
		readed = ft_strjoin(aux, buffer);
		if (aux != NULL)
			free(aux);
		end = analyze_str(readed);
	}
	line = malloc((end + 2) * sizeof(char));
	ft_strlcpy(line, readed, (end + 2));
	aux = ft_strdup((const char *)readed);
	if (readed != NULL)
		free(readed);
	readed = ft_substr(aux, end + 1,  ft_strlen(aux) - (end + 1));
	if (aux != NULL)
		free(aux);
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
		// printf("%s", ptr);
		free(ptr);
		ptr = get_next_line(fd);
	}
	close(fd);
	return (0);
}