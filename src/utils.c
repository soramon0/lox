#include "lox.h"

void	exit_msg(int status, char *fmt, ...)
{
	va_list	args;

	if (fmt != NULL)
	{
		va_start(args, fmt);
		ft_vprintf_fd(args, STDERR_FILENO, fmt);
		va_end(args);
	}
	exit(status);
}

void	exit_err(char *fmt, ...)
{
	va_list	args;

	if (fmt != NULL)
	{
		va_start(args, fmt);
		ft_vprintf_fd(args, STDERR_FILENO, fmt);
		va_end(args);
	}
	exit(EXIT_FAILURE);
}
