#include "lox.h"

void	report(int line, char *where, char *msg)
{
	ft_printf_fd(STDERR_FILENO, "[line %d] Error%s: %s\n", line, where, msg);
}

void	error(int line, char *msg)
{
	report(line, "", msg);
}
