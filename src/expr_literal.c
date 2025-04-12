#include "lox.h"

t_expr	*expr_literal_nbr_create(double value)
{
	t_expr	*expr;

	expr = malloc(sizeof(t_expr));
	if (expr == NULL)
		return (NULL);
	expr->type = EXPR_LITERAL;
	expr->u_as.literal.type = LITERAL_NUMBER;
	expr->u_as.literal.u_value.number = value;
	return (expr);
}

t_expr	*expr_literal_str_create(const char *value)
{
	t_expr	*expr;

	expr = malloc(sizeof(t_expr));
	if (expr == NULL)
		return (NULL);
	expr->type = EXPR_LITERAL;
	expr->u_as.literal.type = LITERAL_STRING;
	expr->u_as.literal.u_value.string = ft_strdup(value);
	return (expr);
}

t_expr	*expr_literal_bool_create(bool value)
{
	t_expr	*expr;

	expr = malloc(sizeof(t_expr));
	if (expr == NULL)
		return (NULL);
	expr->type = EXPR_LITERAL;
	if (value)
		expr->u_as.literal.type = LITERAL_TRUE;
	else
		expr->u_as.literal.type = LITERAL_FALSE;
	return (expr);
}

t_expr	*expr_literal_nil_create(void)
{
	t_expr	*expr;

	expr = malloc(sizeof(t_expr));
	if (expr == NULL)
		return (NULL);
	expr->type = EXPR_LITERAL;
	expr->u_as.literal.type = LITERAL_NIL;
	return (expr);
}

void	expr_literal_free(t_expr *expr)
{
	if (expr == NULL)
		return ;
	if (expr->u_as.literal.type == LITERAL_STRING)
		free(expr->u_as.literal.u_value.string);
	free(expr);
}
