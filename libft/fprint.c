/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:39:53 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/02/13 16:03:10 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	fp_handle_specifier(const char *format, va_list argptr, \
		t_fp_string *string)
{
	if (*format == 'd')
		return (fp_int_specifier(argptr, string));
	else if (*format == 's')
		return (fp_str_specifier(argptr, string));
	else if (*format == '%')
		return (fp_string_fill(string, "%", 1));
	else if (*format == 'c')
		return (fp_char_specifier(argptr, string));
	else if (*format == 'z')
		return (fp_size_t_specifier(argptr, string));
	else if (*format == 'l')
		return (fp_ll_specifier(argptr, string));
	write(2, "Error: fprint cannot parse this string\n", 39);
	return (0);
}

static size_t	fp_parser(char *src, va_list aptr, t_fp_string *string)
{
	size_t		i;
	size_t		begin;
	size_t		length;

	i = 0;
	begin = 0;
	length = 0;
	while (src[i])
	{
		while (src[i] && src[i] != '%')
			i++;
		if (i - begin)
			length += fp_string_fill(string, &(src[begin]), i - begin);
		if (src[i])
		{
			i++;
			length += fp_handle_specifier(&(src[i]), aptr, string);
			if (src[i])
				i++;
		}
		begin = i;
	}
	return (length);
}

size_t	fprint_fd(int fd, const char *format, ...)
{
	va_list		argptr;
	t_fp_string	string;
	size_t		length;

	va_start(argptr, format);
	string.length = 0;
	string.fd = fd;
	length = fp_parser((char *)format, argptr, &string);
	va_end(argptr);
	if (string.length)
		length += fp_string_print(&string);
	return (length);
}

size_t	fprint(const char *format, ...)
{
	va_list		argptr;
	t_fp_string	string;
	size_t		length;

	va_start(argptr, format);
	string.length = 0;
	string.fd = 1;
	length = fp_parser((char *)format, argptr, &string);
	va_end(argptr);
	if (string.length)
		length += fp_string_print(&string);
	return (length);
}
