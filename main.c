#include "src/lox.h"

void	run(char *src)
{
	printf("%s", src);
	free(src);
}

void	runPrompt(void)
{
	char	*line;

	while (1)
	{
		line = readline("shell> ");
		if (line == NULL)
			break ;
		run(line);
	}
}

void	runFile(char *file)
{
	char	*bytes;

	bytes = read_entire_file(file);
	if (bytes == NULL)
	{
		perror(file);
		exit(EX_DATAERR);
	}
	run(bytes);
}

int	main(int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("Usage: jlox [script]\n");
		exit(EX_USAGE);
	}
	else if (argc == 2)
		runFile(argv[1]);
	else
		runPrompt();
	return (EXIT_SUCCESS);
}
