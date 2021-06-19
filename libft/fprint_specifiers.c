/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_specifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:00:42 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/02/13 16:02:18 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	fp_int_specifier(va_list argptr, t_fp_string *string)
{
	size_t		value;
	size_t		copy;
	size_t		output;
	int			sign_value;
	int			length;

	sign_value = (int)va_arg(argptr, int);
	if (sign_value < 0)
		output = fp_string_fill(string, "-", 1);
	else
		output = 0;
	if (sign_value < 0)
		value = (size_t)(-sign_value);
	else
		value = (size_t)sign_value;
	copy = value;
	length = 1;
	copy = copy / 10;
	while (copy)
	{
		length++;
		copy = copy / 10;
	}
	return (output + fp_string_fill_nbr(string, value, length));
}

size_t	fp_str_specifier(va_list argptr, t_fp_string *string)
{
	char		*str;

	str = (char *)va_arg(argptr, char *);
	return (fp_string_fill(string, str, ft_strlen(str)));
}

size_t	fp_char_specifier(va_list argptr, t_fp_string *string)
{
	char		ch;

	ch = (char)va_arg(argptr, int);
	return (fp_string_fill(string, &ch, 1));
}

size_t	fp_ll_specifier(va_list argptr, t_fp_string *string)
{
	size_t		value;
	size_t		copy;
	size_t		output;
	long long	sign_value;
	int			length;

	sign_value = (long long)va_arg(argptr, long long);
	if (sign_value < 0)
		output = fp_string_fill(string, "-", 1);
	else
		output = 0;
	if (sign_value < 0)
		value = (size_t)(-sign_value);
	else
		value = (size_t)sign_value;
	copy = value;
	length = 1;
	copy = copy / 10;
	while (copy)
	{
		length++;
		copy = copy / 10;
	}
	return (output + fp_string_fill_nbr(string, value, length));
}

size_t	fp_size_t_specifier(va_list argptr, t_fp_string *string)
{
	size_t		value;
	size_t		copy;
	int			length;

	value = (size_t)va_arg(argptr, unsigned long long);
	copy = value;
	length = 1;
	copy = copy / 10;
	while (copy)
	{
		length++;
		copy = copy / 10;
	}
	return (fp_string_fill_nbr(string, value, length));
}
