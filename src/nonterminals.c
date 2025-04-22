#include "lox.h"

t_expr	*expression(t_token **token);

bool	token_match(t_token **head, size_t count, ...)
{
	t_token			*current;
	va_list			args;
	t_token_type	type;

	if (head == NULL || *head == NULL)
		return (false);
	current = *head;
	if (current->type == T_EOF)
		return (va_end(args), false);
	va_start(args, count);
	while (count--)
	{
		type = va_arg(args, int);
		if (current->type == type)
		{
			*head = current->next;
			return (va_end(args), true);
		}
	}
	return (va_end(args), false);
}

t_expr	*primary(t_token **token)
{
	t_expr	*expr;

	if (token_match(token, 1, T_FALSE))
		return (expr_literal_bool_create(false));
	else if (token_match(token, 1, T_TRUE))
		return (expr_literal_bool_create(true));
	else if (token_match(token, 1, T_NIL))
		return (expr_literal_nil_create());
	else if (token_match(token, 1, T_NUMBER))
		return (expr_literal_nbr_create(strtod((char *)(*token)->prev->lexeme,
					NULL)));
	else if (token_match(token, 1, T_STRING))
		return (expr_literal_str_create((char *)(*token)->prev->lexeme));
	else if (token_match(token, 1, T_LEFT_PAREN))
	{
		expr = expr_grouping_create(expression(token));
		if (expr == NULL)
			return (NULL);
		if (!token_match(token, 1, T_RIGHT_PAREN))
			return (error((*token)->line, "Expect ')' after expression."),
				expr_free(expr), NULL);
		return (expr);
	}
	return (error((*token)->line, "Expect expression."), NULL);
}

t_expr	*unary(t_token **token)
{
	t_expr	*right;
	t_token	*op;

	if (token_match(token, 2, T_BANG, T_MINUS))
	{
		op = (*token)->prev;
		right = unary(token);
		if (right == NULL)
			return (NULL);
		return (expr_unary_create(op, right));
	}
	return (primary(token));
}

t_expr	*factor(t_token **token)
{
	t_expr	*expr;
	t_expr	*left;
	t_expr	*right;
	t_token	*op;

	left = unary(token);
	if (left == NULL)
		return (NULL);
	while (token_match(token, 2, T_SLASH, T_STAR))
	{
		op = (*token)->prev;
		right = unary(token);
		if (right == NULL)
			return (expr_free(left), NULL);
		expr = expr_binary_create(left, op, right);
		if (expr == NULL)
			return (expr_free(left), expr_free(right), NULL);
		left = expr;
	}
	return (left);
}

t_expr	*term(t_token **token)
{
	t_expr	*expr;
	t_expr	*left;
	t_expr	*right;
	t_token	*op;

	left = factor(token);
	if (left == NULL)
		return (NULL);
	while (token_match(token, 2, T_MINUS, T_PLUS))
	{
		op = (*token)->prev;
		right = factor(token);
		if (right == NULL)
			return (expr_free(left), NULL);
		expr = expr_binary_create(left, op, right);
		if (expr == NULL)
			return (expr_free(left), expr_free(right), NULL);
		left = expr;
	}
	return (left);
}

t_expr	*comparison(t_token **token)
{
	t_expr	*expr;
	t_expr	*left;
	t_expr	*right;
	t_token	*op;

	left = term(token);
	if (left == NULL)
		return (NULL);
	while (token_match(token, 4, T_GREATER, T_GREATER_EQUAL, T_LESS,
			T_LESS_EQUAL))
	{
		op = (*token)->prev;
		right = term(token);
		if (right == NULL)
			return (expr_free(left), NULL);
		expr = expr_binary_create(left, op, right);
		if (expr == NULL)
			return (expr_free(left), expr_free(right), NULL);
		left = expr;
	}
	return (left);
}

t_expr	*equality(t_token **token)
{
	t_expr	*expr;
	t_expr	*left;
	t_expr	*right;
	t_token	*op;

	expr = NULL;
	left = comparison(token);
	if (left == NULL)
		return (NULL);
	while (token_match(token, 2, T_BANG_EQUAL, T_EQUAL_EQUAL))
	{
		op = (*token)->prev;
		right = comparison(token);
		if (right == NULL)
			return (expr_free(left), NULL);
		expr = expr_binary_create(left, op, right);
		if (expr == NULL)
			return (expr_free(left), expr_free(right), NULL);
		left = expr;
	}
	return (left);
}

t_expr	*expression(t_token **token)
{
	if (token == NULL || *token == NULL)
		return (NULL);
	if ((*token)->type == T_EOF)
		return (NULL);
	return (equality(token));
}
