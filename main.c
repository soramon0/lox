#include "src/lox.h"

int	run(char *src)
{
	t_token	*tokens;
	t_token	*head;
	t_expr	*expr;

	tokens = tokens_scan(src);
	if (tokens == NULL)
		return (EX_DATAERR);
	head = tokens;
	expr = expression(&tokens);
	if (tokens->type != T_EOF)
		error(tokens->line, "Invalid syntax");
	else
		ast_print(expr, 0);
	return (expr_free(expr), tokens_free(head), EXIT_SUCCESS);
}

void	run_prompt(void)
{
	char	*line;

	while (1)
	{
		line = readline("shell> ");
		if (line == NULL)
		{
			rl_clear_history();
			printf("exit\n");
			break ;
		}
		run(line);
		if (*line)
			add_history(line);
		free(line);
	}
}

void	run_file(char *file)
{
	char	*bytes;
	int		status;

	bytes = read_entire_file(file);
	if (bytes == NULL)
	{
		perror(file);
		exit(EX_DATAERR);
	}
	status = run(bytes);
	free(bytes);
	exit(status);
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
