
#include <stdlib.h>
#include <stdio.h>

void	assign_memory()
{
	static char	*str;
	char	src[] = "hola";
	int		i;

	i = 0;
	printf("%s \n", str);
	str = malloc(5 * sizeof(char));
	if(!str)
		// return (NULL);
	while(i < 4)
	{
		str[i] = src[i];
		i++;
	}
	free(str);
	// return (str);
}

int		main(void)
{
	char	*str;
	int		i=0;

	while (i < 3)
	{
		assign_memory();
		i++;
	}
	
	return (0);
}