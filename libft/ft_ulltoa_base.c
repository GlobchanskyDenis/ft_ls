/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <kirill@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 17:12:16 by forange-          #+#    #+#             */
/*   Updated: 2019/08/18 14:00:46 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_ulltoa_base_getNextSymbol(unsigned long long dgt, int base)
{
	unsigned long long	number;

	number = dgt % base;
	if (number > 9)
		return ((number - 10) + 'a');
	return (number + '0');
}

char	*ft_ulltoa_base(unsigned long long dgt, int base)
{
	unsigned long long	temp;
	int					i;
	char				*out;

	i = 0;
	if (base < 2 && base > 16)
		return (NULL);
	if (!dgt)
		return (ft_strdup("0"));
	temp = dgt;
	while (temp)
	{
		temp /= base;
		i++;
	}
	out = (char *)malloc(i + 1);
	out[i] = '\0';
	while (dgt)
	{
		i--;
		out[i] = ft_ulltoa_base_getNextSymbol(dgt, base);
		dgt /= base;
	}
	return (out);
}
