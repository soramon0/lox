#include "src/lox.h"

int	run(char *src)
{
	t_token	*tokens;
	t_token	*tmp;

	tokens = tokens_scan(src);
	if (tokens == NULL)
		return (free(src), EX_DATAERR);
	tmp = tokens;
	while (tmp)
	{
		token_str(tmp, true);
		tmp = tmp->next;
	}
	return (free(src), tokens_free(tokens), EXIT_SUCCESS);
}

void	run_prompt(void)
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

void	run_file(char *file)
{
	char	*bytes;

	bytes = read_entire_file(file);
	if (bytes == NULL)
	{
		perror(file);
		exit(EX_DATAERR);
	}
	exit(run(bytes));
}

int	main(int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("Usage: jlox [script]\n");
		exit(EX_USAGE);
	}
	else if (argc == 2)
		run_file(argv[1]);
	else
		run_prompt();
	return (EXIT_SUCCESS);
}
