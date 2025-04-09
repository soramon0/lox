#ifndef SHELL_H
# define SHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sysexits.h>
# include <fcntl.h>

void	exit_msg(int status, char *fmt, ...);
void	exit_err(char *fmt, ...);
char	*read_entire_file(char *file);

#endif
