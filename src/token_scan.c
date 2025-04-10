#include "lox.h"

t_token	*tokens_scan(char *src)
{
	t_token	*token;

	token = token_new(T_VAR, "name", "KARIM", 1);
	if (token == NULL)
		return (error(1, "token_new: failed"), NULL);
	(void)src;
	token_str(token, true);
	return (token);
}
