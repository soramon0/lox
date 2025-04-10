#include "lox.h"

const char	*token_type_str4(t_token_type type);
const char	*token_type_str3(t_token_type type);
const char	*token_type_str2(t_token_type type);

const char	*token_type_str(t_token_type type)
{
	if (type == T_MINUS)
		return ("T_MINUS");
	if (type == T_PLUS)
		return ("T_PLUS");
	if (type == T_SEMICOLON)
		return ("T_SEMICOLON");
	if (type == T_SLASH)
		return ("T_SLASH");
	if (type == T_STAR)
		return ("T_STAR");
	if (type == T_BANG)
		return ("T_BANG");
	if (type == T_BANG_EQUAL)
		return ("T_BANG_EQUAL");
	if (type == T_EQUAL)
		return ("T_EQUAL");
	if (type == T_EQUAL_EQUAL)
		return ("T_EQUAL_EQUAL");
	return (token_type_str2(type));
}

const char	*token_type_str2(t_token_type type)
{
	if (type == T_GREATER)
		return ("T_GREATER");
	if (type == T_GREATER_EQUAL)
		return ("T_GREATER_EQUAL");
	if (type == T_LESS)
		return ("T_LESS");
	if (type == T_LESS_EQUAL)
		return ("T_LESS_EQUAL");
	if (type == T_IDENTIFIER)
		return ("T_IDENTIFIER");
	if (type == T_STRING)
		return ("T_STRING");
	if (type == T_NUMBER)
		return ("T_NUMBER");
	if (type == T_AND)
		return ("T_AND");
	if (type == T_CLASS)
		return ("T_CLASS");
	if (type == T_ELSE)
		return ("T_ELSE");
	if (type == T_FALSE)
		return ("T_FALSE");
	if (type == T_FUN)
		return ("T_FUN");
	return (token_type_str3(type));
}

const char	*token_type_str3(t_token_type type)
{
	if (type == T_FOR)
		return ("T_FOR");
	if (type == T_IF)
		return ("T_IF");
	if (type == T_NIL)
		return ("T_NIL");
	if (type == T_OR)
		return ("T_OR");
	if (type == T_PRINT)
		return ("T_PRINT");
	if (type == T_RETURN)
		return ("T_RETURN");
	if (type == T_SUPER)
		return ("T_SUPER");
	if (type == T_THIS)
		return ("T_THIS");
	if (type == T_TRUE)
		return ("T_TRUE");
	if (type == T_VAR)
		return ("T_VAR");
	if (type == T_WHILE)
		return ("T_WHILE");
	if (type == T_EOF)
		return ("T_EOF");
	return (token_type_str4(type));
}

const char	*token_type_str4(t_token_type type)
{
	if (type == T_LEFT_PAREN)
		return ("T_LEFT_PAREN");
	if (type == T_RIGHT_PAREN)
		return ("T_RIGHT_PAREN");
	if (type == T_LEFT_BRACE)
		return ("T_LEFT_BRACE");
	if (type == T_RIGHT_BRACE)
		return ("T_RIGHT_BRACE");
	if (type == T_COMMA)
		return ("T_COMMA");
	if (type == T_DOT)
		return ("T_DOT");
	return (NULL);
}
