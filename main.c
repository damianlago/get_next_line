#include "get_next_line.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char *line;
	int i = 1;
	fd = open("test.txt", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	//system("leaks a.out");
	return (0);
}