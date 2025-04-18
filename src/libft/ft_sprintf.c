/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	process(va_list args, t_str_builder *sb, char **fmt, char target)
{
	int		bytes;
	bool	r;

	bytes = sb->len;
	r = false;
	if (target == '%')
		r = sb_append_char(sb, '%');
	else if (target == 'c')
		r = sb_append_char(sb, va_arg(args, int));
	else if (target == 's')
		r = sb_append_str(sb, va_arg(args, char *), 0);
	else if (target == 'd' || target == 'i')
		r = sb_append_nbr(sb, va_arg(args, int));
	else if (target == 'u')
		r = sb_append_unbr(sb, va_arg(args, int));
	else if (target == 'x' || target == 'X')
		r = sb_append_hex(sb, va_arg(args, unsigned int), target == 'X');
	else if (target == 'p')
		r = sb_append_ptr(sb, va_arg(args, void *));
	*fmt += 2;
	if (!r)
		return (-1);
	return (sb->len - bytes);
}

static int	handle_specifier(va_list args, t_str_builder *sb, char **s)
{
	char	*specifier;
	int		r;
	int		bytes;

	bytes = 0;
	specifier = ft_strchr("cspdiuxX%", *((*s) + 1));
	if (!specifier)
	{
		if (!sb_append_char(sb, '%'))
			return (-1);
		bytes++;
		s++;
	}
	else
	{
		r = process(args, sb, s, *specifier);
		if (r == -1)
			return (-1);
		bytes += r;
	}
	return (bytes);
}

int	ft_vsprintf(va_list args, char **buff, const char *s, ...)
{
	int				bytes;
	int				r;
	t_str_builder	*sb;

	if (!s || !buff)
		return (-1);
	sb = sb_create(ft_strlen(s));
	if (sb == NULL)
		return (-1);
	bytes = 0;
	while (*s)
	{
		if (*s != '%' && ++bytes)
		{
			if (!sb_append_char(sb, *s))
				return (*buff = NULL, sb_free(sb), -1);
			s++;
			continue ;
		}
		r = handle_specifier(args, sb, (char **)&s);
		if (r == -1)
			return (*buff = NULL, sb_free(sb), -1);
		bytes += r;
	}
	return (*buff = sb_build(sb), bytes);
}

int	ft_sprintf(char **buff, const char *format, ...)
{
	int		bytes;
	va_list	args;

	if (!format || !buff)
		return (-1);
	va_start(args, format);
	bytes = ft_vsprintf(args, buff, format);
	va_end(args);
	return (bytes);
}
