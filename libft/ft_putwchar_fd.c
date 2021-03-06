/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forange- <forange-@student.fr.42>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:28:14 by forange-          #+#    #+#             */
/*   Updated: 2019/08/10 17:41:08 by forange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_putwchar_fd_handler(wchar_t c, int fd)
{
	ft_putchar_fd_smpl(0xF0 | (c >> 18), fd);
	ft_putchar_fd_smpl(0x80 | ((c >> 12) & 0x3F), fd);
	ft_putchar_fd_smpl(0x80 | ((c >> 6) & 0x3F), fd);
	ft_putchar_fd_smpl(0x80 | (c & 0x3F), fd);
	return (4);
}

size_t	ft_putwchar_fd(wchar_t c, int fd)
{
	if (c < 0x80)
		ft_putchar_fd_smpl(c, fd);
	else if (c < 0x800)
	{
		ft_putchar_fd_smpl((0xC0 | (c >> 6)), fd);
		ft_putchar_fd_smpl(0x80 | (c & 0x3F), fd);
		return (2);
	}
	else if (c < 0x10000)
	{
		ft_putchar_fd_smpl(0xE0 | (c >> 12), fd);
		ft_putchar_fd_smpl(0x80 | ((c >> 6) & 0x3F), fd);
		ft_putchar_fd_smpl(0x80 | (c & 0x3F), fd);
		return (3);
	}
	else if (c < 0x200000)
		return (ft_putwchar_fd_handler(c, fd));
	if (c < 0x80)
		return (1);
	return (-1);
}
