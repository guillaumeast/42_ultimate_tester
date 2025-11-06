#include <stdio.h>
#include "get_next_line.h"

static void	run_tests(int fd);

int	main(int argc, char **argv)
{
	int		fd;

	if (argc > 2)
	{
		fprintf(stderr, "Usage for stdin parsing: ./a.out\n");
		fprintf(stderr, "Usage for file parsing:  ./a.out <filepath>\n");
		return (1);
	}
	if (argc == 1)
		run_tests(STDIN_FILENO);
	else
	{
		fd = open(argv[1], O_RDONLY);
		run_tests(fd);
		close(fd);
	}
	return (0);
}

static void	run_tests(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		fflush(stdout);
		free(line);
	}
}
