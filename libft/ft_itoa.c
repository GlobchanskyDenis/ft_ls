/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:40:39 by bsabre-c          #+#    #+#             */
/*   Updated: 2018/12/01 16:24:34 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_countRanks(int src)
{
	int	rank;

	rank = 1;
	src = src / 10;
	while (src)
	{
		rank++;
		src = src / 10;
	}
	return (rank);
}

char	*ft_itoa(int n)
{
	char			*dst;
	int				ranks;
	int				sign;
	unsigned int	temp;

	ranks = ft_itoa_countRanks(n);
	sign = 0;
	if (n < 0)
		sign = 1;
	if (n < 0)
		temp = (unsigned int)(-n);
	else
		temp = (unsigned int)n;
	dst = (char *)malloc(ranks + sign + 1);
	if (!(dst))
		return (NULL);
	dst[ranks + sign] = '\0';
	while (--ranks > -1)
	{
		dst[ranks + sign] = (char)(temp % 10 + '0');
		temp = temp / 10;
	}
	if (sign)
		dst[0] = '-';
	return (dst);
}
