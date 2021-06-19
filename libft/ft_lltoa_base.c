/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <kirill@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 17:17:29 by forange-          #+#    #+#             */
/*   Updated: 2019/08/21 22:31:17 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lltoa_base_countRanks(long long dgt, int base)
{
	int	ranks;

	ranks = 1;
	dgt = ft_absll(dgt);
	dgt = dgt / base;
	while (dgt)
	{
		ranks++;
		dgt = dgt / base;
	}
	return (ranks);
}

static char	ft_lltoa_base_returnNextSymbolWithBase(unsigned long long dgt, \
	int base)
{
	unsigned long long	value;

	value = dgt % base;
	if (value > 9)
		return ((char)(value - 10) + 'a');
	return ((char)value + '0');
}

char	*ft_lltoa_base(long long dgt, int base)
{
	unsigned long long	temp;
	int					ranks;
	char				*out;
	int					negative;

	negative = 0;
	if (dgt < 0)
		negative = 1;
	if (base < 2 && base > 16)
		return (NULL);
	if (!dgt)
		return (ft_strdup("0"));
	ranks = ft_lltoa_base_countRanks(dgt, base);
	out = (char *)ft_memalloc(ranks + negative + 1);
	if (dgt < 0)
		out[0] = '-';
	temp = ft_absll(dgt);
	while (temp)
	{
		out[--ranks + negative] = \
			ft_lltoa_base_returnNextSymbolWithBase(temp, base);
		temp /= base;
	}
	return (out);
}
