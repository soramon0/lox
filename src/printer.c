#include "lox.h"

void	ast_print(t_expr *root)
{
	if (root == NULL)
		printf("empty");
	else if (root->type == EXPR_LITERAL)
	{
		if (root->u_as.literal.type == LITERAL_NIL)
			printf("nil");
		else if (root->u_as.literal.type == LITERAL_TRUE)
			printf("true");
		else if (root->u_as.literal.type == LITERAL_FALSE)
			printf("false");
		else if (root->u_as.literal.type == LITERAL_STRING)
			printf("%s", root->u_as.literal.u_value.string);
		else if (root->u_as.literal.type == LITERAL_NUMBER)
			printf("%lf", root->u_as.literal.u_value.number);
		else
			printf("<?>");
	}
	else if (root->type == EXPR_GROUPING)
	{
		printf("(group ");
		ast_print(root->u_as.grouping.expression);
		printf(")");
	}
	else if (root->type == EXPR_UNARY)
	{
		printf("(%s ", root->u_as.unary.op->lexeme);
		ast_print(root->u_as.unary.right);
		printf(")");
	}
	else if (root->type == EXPR_BINARY)
	{
		printf("(%s ", root->u_as.binary.op->lexeme);
		ast_print(root->u_as.binary.left);
		ast_print(root->u_as.binary.right);
		printf(")");
	}
}
