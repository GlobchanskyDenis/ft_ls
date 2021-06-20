/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fgnl_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:37:59 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/02/18 13:47:17 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	FGNL - Fast Get Next Line functions.
**	This functions can read from source by fd and return strings line by line.
**	-------------------------------------------
**	With this function you can delete all data that stores in heap
*/

void	fgnl_free(void)
{
	int						i;

	i = 0;
	while (i < FGNL_FD_MAX)
	{
		fgnl_head(i, "delete");
		i++;
	}
}

/*
**	With this function you can directly create, get and delete header
**	of fgnl function.
*/

t_fgnl_string	**fgnl_head(int fd, char *command)
{
	static t_fgnl_string	*head[FGNL_FD_MAX];

	if (fd < 0 || fd > FGNL_FD_MAX || !command)
		return (NULL);
	if (!ft_strcmp(command, "create"))
	{
		fgnl_head(fd, "delete");
		head[fd] = fgnl_lstnew(NULL, 0);
		return (&(head[fd]));
	}
	else if (!ft_strcmp(command, "delete"))
	{
		if (head[fd])
			fgnl_lstdel(&(head[fd]));
		return (NULL);
	}
	else if (!ft_strcmp(command, "get"))
		return (&(head[fd]));
	return (NULL);
}

t_fgnl_string	*fgnl_lstnew(const char *src, size_t length)
{
	t_fgnl_string			*dst;

	dst = (t_fgnl_string *)malloc(sizeof(t_fgnl_string));
	if (!dst)
		return (NULL);
	if (src)
		ft_memcpy(dst->str, src, length);
	dst->length = length;
	dst->next = NULL;
	return (dst);
}

void	fgnl_lstdel(t_fgnl_string **head)
{
	t_fgnl_string			*lst;
	t_fgnl_string			*to_delete;

	lst = *head;
	while (lst)
	{
		to_delete = lst;
		lst = lst->next;
		free(to_delete);
	}
	*head = NULL;
}
