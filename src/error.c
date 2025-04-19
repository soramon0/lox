#include "lox.h"

void	report(int line, char *where, char *msg)
{
	ft_printf_fd(STDERR_FILENO, "[line %d] Error%s: %s\n", line, where, msg);
}

void	error(int line, char *msg, ...)
{
	va_list	args;
	char	*buff;

	buff = NULL;
	va_start(args, msg);
	ft_vsprintf(args, &buff, msg);
	if (buff == NULL)
		return ;
	report(line, "", buff);
	free(buff);
	va_end(args);
}
