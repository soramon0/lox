#include "lox.h"

void	expr_free(t_expr *expr)
{
	if (expr == NULL)
		return ;
	else if (expr->type == EXPR_LITERAL)
		expr_literal_free(expr);
	else if (expr->type == EXPR_UNARY)
	{
		expr_free(expr->u_as.unary.right);
		expr_unary_free(expr);
	}
	else if (expr->type == EXPR_BINARY)
	{
		expr_free(expr->u_as.binary.left);
		expr_free(expr->u_as.binary.right);
		expr_binary_free(expr);
	}
	else if (expr->type == EXPR_GROUPING)
	{
		expr_free(expr->u_as.grouping.expression);
		expr_grouping_free(expr);
	}
}
