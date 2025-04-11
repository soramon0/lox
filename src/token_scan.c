#include "lox.h"

t_token	*scan_token(char *src, size_t *current, size_t line)
{
	char	c;

	c = src[(*current)++];
	if (c == '(')
		return (token_new(T_LEFT_PAREN, NULL, NULL, line));
	if (c == ')')
		return (token_new(T_RIGHT_PAREN, NULL, NULL, line));
	if (c == '{')
		return (token_new(T_LEFT_BRACE, NULL, NULL, line));
	if (c == '}')
		return (token_new(T_RIGHT_BRACE, NULL, NULL, line));
	if (c == ',')
		return (token_new(T_COMMA, NULL, NULL, line));
	if (c == '.')
		return (token_new(T_DOT, NULL, NULL, line));
	if (c == '-')
		return (token_new(T_MINUS, NULL, NULL, line));
	if (c == '+')
		return (token_new(T_PLUS, NULL, NULL, line));
	if (c == ';')
		return (token_new(T_SEMICOLON, NULL, NULL, line));
	if (c == '*')
		return (token_new(T_STAR, NULL, NULL, line));
	return (NULL);
}

t_token	*tokens_scan(char *src)
{
	size_t	current;
	size_t	line;
	t_token	*head;
	t_token	*last;

	current = 0;
	line = 1;
	head = NULL;
	while (src[current])
	{
		if (src[current] == '\n' && ++current && ++line)
			continue ;
		if (head == NULL)
		{
			head = scan_token(src, &current, line);
			if (head == NULL)
				return (NULL);
			last = head;
		}
		else
		{
			last->next = scan_token(src, &current, line);
			if (last->next == NULL)
				return (tokens_free(head), NULL);
			last = last->next;
		}
	}
	last->next = token_new(T_EOF, "", NULL, line);
	if (last->next == NULL)
		return (tokens_free(head), NULL);
	return (head);
}
