/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:01:50 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/18 23:39:27 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include "get_next_line.h"
# include <stdio.h>

int	main(int argc, char *argv[])
{
	int		fd;
	char	*ptr;
	
	if (argc == 1)
	{
		printf("Enter name file");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
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
	// system("leaks -q a.out");
	return (0);
}
