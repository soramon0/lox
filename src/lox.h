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

	T_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	size_t			line;
	char			*lexeme;
	void			*literal;
	char			*str;
	struct s_token	*next;
}					t_token;

void				exit_msg(int status, char *fmt, ...);
void				exit_err(char *fmt, ...);
void				report(int line, char *where, char *msg);
void				error(int line, char *msg);

char				*read_entire_file(char *file);
t_token				*token_new(t_token_type type, char *lexeme, void *literal,
						size_t line);
t_token				*tokens_scan(char *src);
void				tokens_free(t_token *token);
void				token_free(t_token *token);
void				token_str(t_token *t, bool nl);
const char			*token_type_str(t_token_type type);

#endif
