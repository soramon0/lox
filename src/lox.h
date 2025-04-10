#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sysexits.h>

void	exit_msg(int status, char *fmt, ...);
void	exit_err(char *fmt, ...);
char	*read_entire_file(char *file);

#endif
