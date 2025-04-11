#include "lox.h"

bool	match(char *src, size_t *current, char expected)
{
	if (!src[*current])
		return (false);
	if (src[*current] == expected)
	{
		*current += 1;
		return (true);
	}
	return (false);
}

t_token	*scan_token(char *src, size_t *current, size_t *line)
{
	char	c;
	size_t	len;

	c = src[(*current)++];
	if (c == '(')
		return (token_new(T_LEFT_PAREN, NULL, NULL, *line));
	if (c == ')')
		return (token_new(T_RIGHT_PAREN, NULL, NULL, *line));
	if (c == '{')
		return (token_new(T_LEFT_BRACE, NULL, NULL, *line));
	if (c == '}')
		return (token_new(T_RIGHT_BRACE, NULL, NULL, *line));
	if (c == ',')
		return (token_new(T_COMMA, NULL, NULL, *line));
	if (c == '.')
		return (token_new(T_DOT, NULL, NULL, *line));
	if (c == '-')
		return (token_new(T_MINUS, NULL, NULL, *line));
	if (c == '+')
		return (token_new(T_PLUS, NULL, NULL, *line));
	if (c == ';')
		return (token_new(T_SEMICOLON, NULL, NULL, *line));
	if (c == '*')
		return (token_new(T_STAR, NULL, NULL, *line));
	if (c == '!')
	{
		if (match(src, current, '='))
			return (token_new(T_BANG_EQUAL, NULL, NULL, *line));
		return (token_new(T_BANG, NULL, NULL, *line));
	}
	if (c == '=')
	{
		if (match(src, current, '='))
			return (token_new(T_EQUAL_EQUAL, NULL, NULL, *line));
		return (token_new(T_EQUAL, NULL, NULL, *line));
	}
	if (c == '<')
	{
		if (match(src, current, '='))
			return (token_new(T_LESS_EQUAL, NULL, NULL, *line));
		return (token_new(T_LESS, NULL, NULL, *line));
	}
	if (c == '>')
	{
		if (match(src, current, '='))
			return (token_new(T_GREATER_EQUAL, NULL, NULL, *line));
		return (token_new(T_GREATER, NULL, NULL, *line));
	}
	if (c == ' ' || c == '\r' || c == '\t')
		return (NULL);
	if (c == '/')
	{
		if (match(src, current, '/'))
		{
			len = ft_strlen(src);
			while (src[*current] && *current <= len && src[*current] != '\n')
				*current += 1;
			c = src[*current];
			if (!c)
				return (NULL);
		}
		else
			return (token_new(T_SLASH, NULL, NULL, *line));
	}
	if (c == '\n')
		return (((*line)++), NULL);
	error(*line, "Unexpected character.");
	return (token_new(T_UNKNOWN, NULL, NULL, *line));
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
		if (head == NULL)
		{
			head = scan_token(src, &current, &line);
			if (head == NULL)
				continue ;
			last = head;
		}
		else
		{
			last->next = scan_token(src, &current, &line);
			if (last->next == NULL)
				continue ;
			last = last->next;
		}
	}
	if (head == NULL)
		head = token_new(T_EOF, "", NULL, line);
	else
	{
		last->next = token_new(T_EOF, "", NULL, line);
		if (last->next == NULL)
			return (tokens_free(head), NULL);
	}
	return (head);
}
