/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:04:28 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/10 20:47:03 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	ssize_t		bytes;

	bytes = read(fd, buffer, 12);
	if (bytes == -1 || bytes == 0)
		return (NULL);
	return (ft_strdup((const char *)buffer));
}

// # include <fcntl.h>
// # include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*ptr;

// 	fd = open("files/1.txt", O_RDONLY);
// 	if(fd == ERROR)
// 		return(1);
// 	ptr = get_next_line(fd);
// 	while (ptr != NULL)
// 	{
// 		printf("%s", ptr);
// 		free(ptr);
// 		ptr = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }