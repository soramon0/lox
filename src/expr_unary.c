#include "lox.h"

t_expr	*expr_unary_create(t_token *op, t_expr *right)
{
	t_expr	*expr;

	if (op == NULL || right == NULL)
		return (NULL);
	expr = malloc(sizeof(t_expr));
	if (expr == NULL)
		return (NULL);
	expr->type = EXPR_UNARY;
	expr->u_as.unary.right = right;
	expr->u_as.unary.op = op;
	return (expr);
}

void	expr_unary_free(t_expr *expr)
{
	if (expr == NULL)
		return ;
	free(expr);
}
