/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:05:11 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/25 23:01:09 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include "gnl/get_next_line_bonus.h"
# include <stdio.h>

int main(int argc, char *argv[])
{
	int	i;
	int	*fds;
	char **ptrs; 
    int anyFileHasLine;

    if (argc <= 1)
    {
        printf("Usage: %s file1 file2 file3 ...", argv[0]);
        return 1;
    }
    fds = (int *)malloc((argc - 1) * sizeof(int));
    if (fds == NULL)
    {
        perror("Error allocating memory for file descriptors");
        return 1;
    }
	i = 0;
    while (i < argc - 1)
    {
        fds[i] = open(argv[i + 1], O_RDONLY);
        if (fds[i] == ERROR)
        {
            perror("Error opening file");
            free(fds);
            return 1;
        }
		i++;
    }
   	ptrs = (char **)malloc((argc - 1) * sizeof(char *));
    if (ptrs == NULL)
    {
        perror("Error allocating memory for pointers");
        free(fds);
        return 1;
    }
    do
    {
        anyFileHasLine = 0;
        for (int i = 0; i < argc - 1; ++i)
        {
            ptrs[i] = get_next_line(fds[i]);
            if (ptrs[i] != NULL)
                anyFileHasLine = 1;
        }
        for (int i = 0; i < argc - 1; ++i)
        {
            printf("file %d: %s", i + 1, ptrs[i]);
            if (ptrs[i] != NULL)
            {
                free(ptrs[i]);
            }
        }
    } while (anyFileHasLine);
    for (int i = 0; i < argc - 1; ++i)
    {
        close(fds[i]);
    }
    free(ptrs);
    free(fds);
    return 0;
}

/*
int	main(int argc, char *argv[])
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*ptr1;
	char	*ptr2;
	char	*ptr3;
	
	if (argc == 1)
	{
		printf("Enter name file");
		return (1);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY);
	if(fd1 == ERROR)
		return(1);
	if(fd2 == ERROR)
		return(1);
	if(fd3 == ERROR)
		return(1);
	ptr1 = get_next_line(fd1);
	ptr2 = get_next_line(fd2);
	ptr3 = get_next_line(fd3);
	while (ptr1 != NULL || ptr2 != NULL || ptr3 != NULL )
	{
		printf("%s", ptr1);
		printf("%s", ptr2);
		printf("%s", ptr3);
		if(ptr1)
			free(ptr1);
		if(ptr2)
			free(ptr2);
		if(ptr3)
			free(ptr3);
		ptr1 = get_next_line(fd1);
		ptr2 = get_next_line(fd2);
		ptr3 = get_next_line(fd3);
	}
	printf("%s", ptr1);
	printf("%s", ptr2);
	printf("%s", ptr3);
	close(fd1);
	close(fd2);
	close(fd3);
	// system("leaks -q a.out");
	return (0);
}*/
