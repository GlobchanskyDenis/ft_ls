/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_string_operations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:29:15 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/02/13 16:02:50 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

size_t	fp_string_fill_nbr(t_fp_string *string, size_t value, int length)
{
	char	*str;
	size_t	output;

	output = 0;
	if ((size_t)length > MAX_STRING_VECTOR - string->length)
		output = fp_string_print(string);
	str = string->str + string->length;
	string->length += (size_t)length;
	while (--length >= 0)
	{
		str[length] = (char)(value % 10 + '0');
		value = value / 10;
	}
	return (output);
}

size_t	fp_string_fill(t_fp_string *string, char *src, size_t length)
{
	size_t	i;
	char	*str;
	size_t	len;
	size_t	output;

	output = 0;
	if (string->length == MAX_STRING_VECTOR)
		output = fp_string_print(string);
	len = MAX_STRING_VECTOR - string->length;
	if (len > length)
		len = length;
	i = -1;
	str = &(string->str[string->length]);
	while (++i < len)
		str[i] = src[i];
	string->length += len;
	if (len < length)
		output += fp_string_fill(string, &(src[len]), length - len);
	return (output);
}

size_t	fp_string_print(t_fp_string *string)
{
	size_t	length;

	write(string->fd, string->str, string->length);
	length = string->length;
	string->length = 0;
	return (length);
}
