#include "lox.h"

t_expr	*expr_binary_create(t_expr *left, t_token *op, t_expr *right)
{
	t_expr	*expr;

	expr = malloc(sizeof(t_expr));
	if (expr == NULL)
		return (NULL);
	expr->type = EXPR_BINARY;
	expr->u_as.binary.left = left;
	expr->u_as.binary.right = right;
	expr->u_as.binary.op = op;
	return (expr);
}

void	expr_binary_free(t_expr *expr)
{
	if (expr == NULL)
		return ;
	token_free(expr->u_as.binary.op);
	free(expr);
}
