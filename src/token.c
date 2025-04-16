#include "lox.h"

char	*token_str_create(t_token *t)
{
	char	*str;
	char	*str_full;
	char	*type;

	str_full = NULL;
	type = (char *)token_type_str(t->type);
	if (!t->lexeme)
		return (type);
	str = ft_strjoin((char *)type, t->lexeme, ' ');
	if (str == NULL)
		return (type);
	if (t->literal)
		str_full = ft_strjoin(str, t->literal, ' ');
	if (str_full == NULL)
		return (str);
	return (free(str), str_full);
}

t_token	*token_new(t_token_type type, char *lexeme, void *literal, size_t line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->lexeme = lexeme;
	token->literal = literal;
	token->line = line;
	token->str = token_str_create(token);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	token_free(t_token *t)
{
	if (t == NULL)
		return ;
	if (t->lexeme || t->literal)
		free(t->str);
	if (t->type == T_STRING || t->type == T_NUMBER || t->type == T_IDENTIFIER
		|| t->type == T_UNKNOWN)
		free(t->lexeme);
	free(t);
}

void	tokens_free(t_token *token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	while (token)
	{
		tmp = token->next;
		token_free(token);
		token = tmp;
	}
}

void	token_str(t_token *t, bool nl)
{
	if (nl)
		printf("%s\n", t->str);
	else
		printf("%s", t->str);
}
