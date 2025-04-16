#include "lox.h"

t_expr	*expr_grouping_create(t_expr *expression)
{
	t_expr	*expr;

	if (expression == NULL)
		return (NULL);
	expr = malloc(sizeof(t_expr));
	if (expr == NULL)
		return (NULL);
	expr->type = EXPR_GROUPING;
	expr->u_as.grouping.expression = expression;
	return (expr);
}

void	expr_grouping_free(t_expr *expr)
{
	if (expr == NULL)
		return ;
	free(expr);
}
