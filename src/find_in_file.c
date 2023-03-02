#include "automate.h"

void	find_in_file(t_data *data, char *filename)
{
	char buff[MAX_SIZE];
	int fd = open(filename, O_RDONLY);
	int rd, i = 0;

	if (fd < 0)
	{
		printf("Error\n");
		exit (1);
	}
	while (1)
	{
		rd = read(fd, &buff[i], 1);
		if (rd < 0)
			exit (0);
		if (rd == 0 || buff[i] == ' ' || buff[i] == '\n')
		{
			buff[i] = '\0';
			if (find_word(data, buff))
				printf("%s\n", buff);
			i = 0;
			if (rd == 0)
				break ;
			continue;
		}
		i++;
	}
}
