#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sysexits.h>

typedef enum e_token_type
{
	// Single-character tokens.
	T_LEFT_PAREN,
	T_RIGHT_PAREN,
	T_LEFT_BRACE,
	T_RIGHT_BRACE,
	T_COMMA,
	T_DOT,
	T_MINUS,
	T_PLUS,
	T_SEMICOLON,
	T_SLASH,
	T_STAR,
	// One or two character tokens.
	T_BANG,
	T_BANG_EQUAL,
	T_EQUAL,
	T_EQUAL_EQUAL,
	T_GREATER,
	T_GREATER_EQUAL,
	T_LESS,
	T_LESS_EQUAL,
	// Literals.
	T_IDENTIFIER,
	T_STRING,
	T_NUMBER,
	// Keywords.
	T_AND,
	T_CLASS,
	T_ELSE,
	T_FALSE,
	T_FUN,
	T_FOR,
	T_IF,
	T_NIL,
	T_OR,
	T_PRINT,
	T_RETURN,
	T_SUPER,
	T_THIS,
	T_TRUE,
	T_VAR,
	T_WHILE,
	T_EOF,
	T_SKIPPABLE,
	T_UNKNOWN
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	size_t				line;
	char				*lexeme;
	void				*literal;
	char				*str;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef enum e_expr_type
{
	EXPR_LITERAL,
	EXPR_GROUPING,
	EXPR_UNARY,
	EXPR_BINARY,
}						t_expr_type;

typedef struct s_expr	t_expr;

typedef enum e_literal_type
{
	LITERAL_NUMBER,
	LITERAL_STRING,
	LITERAL_TRUE,
	LITERAL_FALSE,
	LITERAL_NIL,
}						t_literal_type;

typedef struct s_expr_literal
{
	t_literal_type		type;
	union
	{
		double			number;
		char			*string;
	} u_value;
}						t_expr_literal;

typedef struct t_expr_binary
{
	t_expr				*left;
	t_token				*op;
	t_expr				*right;
}						t_expr_binary;

typedef struct t_expr_unary
{
	t_token				*op;
	t_expr				*right;
}						t_expr_unary;

typedef struct t_expr_grouping
{
	t_expr				*expression;
}						t_expr_grouping;

typedef struct s_expr
{
	t_expr_type			type;
	union
	{
		t_expr_literal	literal;
		t_expr_binary	binary;
		t_expr_unary	unary;
		t_expr_grouping	grouping;
	} u_as;
}						t_expr;

void					exit_msg(int status, char *fmt, ...);
void					exit_err(char *fmt, ...);
void					report(int line, char *where, char *msg);
void					error(int line, char *msg);

char					*read_entire_file(char *file);
t_token					*token_new(t_token_type type, char *lexeme,
							void *literal, size_t line);
t_token					*tokens_scan(char *src);
void					tokens_free(t_token *token);
void					token_free(t_token *token);
void					token_str(t_token *t, bool nl);
const char				*token_type_str(t_token_type type);

void					expr_free(t_expr *expr);
t_expr					*expr_binary_create(t_expr *l, t_token *op, t_expr *r);
void					expr_binary_free(t_expr *expr);
t_expr					*expr_unary_create(t_token *op, t_expr *r);
void					expr_unary_free(t_expr *expr);
t_expr					*expr_literal_nbr_create(double value);
t_expr					*expr_literal_str_create(const char *value);
t_expr					*expr_literal_bool_create(bool value);
t_expr					*expr_literal_nil_create(void);
void					expr_literal_free(t_expr *expr);
t_expr					*expr_grouping_create(t_expr *expression);
void					expr_grouping_free(t_expr *expression);

t_expr					*expression(t_token **token);

void					ast_print(t_expr *root, int depth);

#endif
