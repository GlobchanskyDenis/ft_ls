/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:38:47 by bsabre-c          #+#    #+#             */
/*   Updated: 2018/12/11 19:04:12 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lltoa_countRanks(long long dgt)
{
	int	ranks;

	ranks = 1;
	dgt = ft_absll(dgt);
	dgt = dgt / 10;
	while (dgt)
	{
		ranks++;
		dgt = dgt / 10;
	}
	return (ranks);
}

char	*ft_lltoa(long long n)
{
	int			len;
	int			is_neg;
	char		*dst;

	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	len = ft_lltoa_countRanks(n);
	dst = (char *)malloc(sizeof(char) * (len + is_neg + 1));
	if (!(dst))
		return (NULL);
	if (is_neg)
		dst[0] = '-';
	dst[len + is_neg] = '\0';
	while (--len >= 0)
	{
		dst[len + is_neg] = (char)(ft_absll(n) % 10 + '0');
		n = n / 10;
	}
	return (dst);
}
