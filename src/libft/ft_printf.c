/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vprintf_fd(va_list args, int fd, const char *format, ...)
{
	int		bytes;
	char	*buff;

	if (!format)
		return (-1);
	buff = NULL;
	bytes = ft_vsprintf(args, &buff, format);
	if (buff == NULL)
		return (-1);
	bytes = write(fd, buff, bytes);
	return (free(buff), bytes);
}

int	ft_vprintf(va_list args, const char *format, ...)
{
	return (ft_vprintf_fd(args, STDOUT_FILENO, format));
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		bytes;

	if (!format)
		return (-1);
	va_start(args, format);
	bytes = ft_vprintf_fd(args, fd, format);
	va_end(args);
	return (bytes);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		bytes;

	if (!format)
		return (-1);
	va_start(args, format);
	bytes = ft_vprintf(args, format);
	va_end(args);
	return (bytes);
}
