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

t_token	*extract_str(char *src, size_t *current, size_t *line)
{
	size_t	start;
	size_t	len;
	char	*substr;

	start = *current;
	len = ft_strlen(src);
	while (src[*current] && src[*current] != '"')
	{
		if (src[*current] == '\n' || *current >= len)
			*line += 1;
		*current += 1;
	}
	if (!src[*current] || *current >= len)
	{
		error(*line, "Unterminated string.");
		return (NULL);
	}
	substr = ft_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	*current += 1;
	return (token_new(T_STRING, substr, NULL, *line));
}

t_token	*extract_nbr(char *src, size_t *current, size_t *line)
{
	size_t	start;
	char	*substr;

	start = *current - 1;
	while (ft_isdigit(src[*current]))
		*current += 1;
	if (src[*current] == '.' && ft_isdigit(src[*current + 1]))
	{
		*current += 1;
		while (ft_isdigit(src[*current]))
			*current += 1;
	}
	substr = ft_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	return (token_new(T_NUMBER, substr, NULL, *line));
}

bool	is_alphanum(char c)
{
	return (ft_isalpha(c) || c == '_' || ft_isdigit(c));
}

t_token	*extract_var(char *src, size_t *current, size_t *line)
{
	t_token_type	type;
	size_t			start;
	char			*substr;
	size_t			len;

	start = *current - 1;
	while (is_alphanum(src[*current]))
		*current += 1;
	len = *current - start;
	substr = ft_substr(src, start, len);
	if (substr == NULL)
		return (NULL);
	type = T_IDENTIFIER;
	if (ft_strncmp(substr, "and", len) == 0 && len == 3)
		type = T_AND;
	if (ft_strncmp(substr, "class", len) == 0 && len == 5)
		type = T_CLASS;
	if (ft_strncmp(substr, "else", len) == 0 && len == 4)
		type = T_ELSE;
	if (ft_strncmp(substr, "false", len) == 0 && len == 5)
		type = T_FALSE;
	if (ft_strncmp(substr, "for", len) == 0 && len == 3)
		type = T_FOR;
	if (ft_strncmp(substr, "fun", len) == 0 && len == 3)
		type = T_FUN;
	if (ft_strncmp(substr, "if", len) == 0 && len == 2)
		type = T_IF;
	if (ft_strncmp(substr, "nil", len) == 0 && len == 3)
		type = T_NIL;
	if (ft_strncmp(substr, "or", len) == 0 && len == 2)
		type = T_OR;
	if (ft_strncmp(substr, "print", len) == 0 && len == 5)
		type = T_PRINT;
	if (ft_strncmp(substr, "return", len) == 0 && len == 6)
		type = T_RETURN;
	if (ft_strncmp(substr, "super", len) == 0 && len == 5)
		type = T_SUPER;
	if (ft_strncmp(substr, "this", len) == 0 && len == 4)
		type = T_THIS;
	if (ft_strncmp(substr, "true", len) == 0 && len == 4)
		type = T_TRUE;
	if (ft_strncmp(substr, "var", len) == 0 && len == 3)
		type = T_VAR;
	if (ft_strncmp(substr, "while", len) == 0 && len == 5)
		type = T_WHILE;
	if (type == T_IDENTIFIER)
		return (token_new(type, substr, NULL, *line));
	return (token_new(type, substr, NULL, *line));
}

void	consume_comment(char *src, size_t *current, size_t *line)
{
	size_t	len;

	len = ft_strlen(src);
	while (src[*current] && *current <= len && src[*current] != '\n')
		*current += 1;
	if (src[*current] == '\n')
	{
		*line += 1;
		*current += 1;
	}
}

void	consume_multicomment(char *src, size_t *current, size_t *line)
{
	size_t	len;

	len = ft_strlen(src);
	while (src[*current] && *current <= len)
	{
		if (src[*current] == '*' && src[*current + 1] == '/')
			break ;
		if (src[*current] == '\n')
			*line += 1;
		*current += 1;
	}
	if (src[*current] == '*' && src[*current + 1] == '/')
		*current += 2;
	if (src[*current] == '\n')
	{
		*line += 1;
		*current += 1;
	}
}

t_token	*scan_token(char *src, size_t *current, size_t *line)
{
	char	c;

	c = src[(*current)++];
	while (c == ' ' || c == '\r' || c == '\t')
		c = src[(*current)++];
	if (c == '\n')
		return (*line += 1, token_new(T_SKIPPABLE, "\n", NULL, *line));
	if (c == '(')
		return (token_new(T_LEFT_PAREN, "(", NULL, *line));
	if (c == ')')
		return (token_new(T_RIGHT_PAREN, ")", NULL, *line));
	if (c == '{')
		return (token_new(T_LEFT_BRACE, "{", NULL, *line));
	if (c == '}')
		return (token_new(T_RIGHT_BRACE, "}", NULL, *line));
	if (c == ',')
		return (token_new(T_COMMA, ",", NULL, *line));
	if (c == '.')
		return (token_new(T_DOT, ".", NULL, *line));
	if (c == '-')
		return (token_new(T_MINUS, "-", NULL, *line));
	if (c == '+')
		return (token_new(T_PLUS, "+", NULL, *line));
	if (c == ';')
		return (token_new(T_SEMICOLON, ";", NULL, *line));
	if (c == '*')
		return (token_new(T_STAR, "*", NULL, *line));
	if (c == '/')
	{
		if (match(src, current, '/'))
			return (consume_comment(src, current, line), NULL);
		if (match(src, current, '*'))
			return (consume_multicomment(src, current, line), NULL);
		return (token_new(T_SLASH, "/", NULL, *line));
	}
	if (c == '!')
	{
		if (match(src, current, '='))
			return (token_new(T_BANG_EQUAL, "!=", NULL, *line));
		return (token_new(T_BANG, "!", NULL, *line));
	}
	if (c == '=')
	{
		if (match(src, current, '='))
			return (token_new(T_EQUAL_EQUAL, "==", NULL, *line));
		return (token_new(T_EQUAL, "=", NULL, *line));
	}
	if (c == '<')
	{
		if (match(src, current, '='))
			return (token_new(T_LESS_EQUAL, "<=", NULL, *line));
		return (token_new(T_LESS, "<", NULL, *line));
	}
	if (c == '>')
	{
		if (match(src, current, '='))
			return (token_new(T_GREATER_EQUAL, ">=", NULL, *line));
		return (token_new(T_GREATER, ">", NULL, *line));
	}
	if (c == '"')
	{
		return (extract_str(src, current, line));
	}
	if (ft_isdigit(c))
		return (extract_nbr(src, current, line));
	if (ft_isalpha(c) || c == '_')
		return (extract_var(src, current, line));
	error(*line, "Unexpected character.");
	return (token_new(T_UNKNOWN, ft_strndup(&src[*current - 1], 1), NULL,
			*line));
}

t_token	*tokens_scan(char *src)
{
	size_t	current;
	size_t	line;
	t_token	*head;
	t_token	*last;
	t_token	*tmp;

	current = 0;
	line = 1;
	head = NULL;
	while (src[current])
	{
		if (head == NULL)
		{
			head = scan_token(src, &current, &line);
			if (head == NULL)
				return (NULL);
			if (head->type == T_SKIPPABLE)
			{
				token_free(head);
				head = NULL;
				continue ;
			}
			last = head;
		}
		else
		{
			last->next = scan_token(src, &current, &line);
			if (last->next == NULL)
				return (tokens_free(head), NULL);
			if (last->next->type == T_SKIPPABLE)
			{
				token_free(last->next);
				last->next = NULL;
				continue ;
			}
			tmp = last;
			last = last->next;
			last->prev = tmp;
		}
	}
	if (head == NULL)
		head = token_new(T_EOF, NULL, NULL, line);
	else
	{
		last->next = token_new(T_EOF, NULL, NULL, line);
		if (last->next == NULL)
			return (tokens_free(head), NULL);
		last->next->prev = last;
	}
	return (head);
}
