#include "lox.h"

char	*token_str_create(t_token *t)
{
	char	*str;
	char	*type;
	int		bytes;

	str = NULL;
	type = (char *)token_type_str(t->type);
	if (!t->lexeme)
		return (type);
	if (t->lexeme && t->literal)
		bytes = ft_sprintf(&str, "%s %s %s", type, t->lexeme, t->literal);
	else
		bytes = ft_sprintf(&str, "%s %s", type, t->lexeme);
	if (bytes == -1)
		return (type);
	return (str);
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
	if (t->type >= T_IDENTIFIER && t->type <= T_NUMBER || t->type == T_UNKNOWN)
		free(t->lexeme);
	if (t->type >= T_AND && t->type <= T_WHILE)
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

void	token_str(t_token *t, bool nl, bool all)
{
	while (t)
	{
		if (nl)
			ft_printf("%s\n", t->str);
		else
			ft_printf("%s", t->str);
		if (all)
			t = t->next;
		else
			break ;
	}
}
