/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fgnl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 20:58:52 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/02/18 13:45:00 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	FGNL - Fast Get Next Line functions.
**	This functions can read from source by fd and return strings line by line.
*/

static size_t	fgnl_find_line_length(t_fgnl_string *lst)
{
	size_t					length;
	size_t					line_length;
	char					*line;

	length = 0;
	while (lst->next)
	{
		length += lst->length;
		lst = lst->next;
	}
	line = lst->str;
	line_length = 0;
	while (line_length < lst->length && line[line_length] && \
			line[line_length] != '\n')
		line_length++;
	return (length + line_length);
}

static void	fgnl_delete_trash(t_fgnl_string **head, size_t length)
{
	t_fgnl_string			*lst;
	t_fgnl_string			*to_free;
	char					*line;

	lst = *head;
	while (lst->next)
	{
		length -= lst->length;
		to_free = lst;
		lst = lst->next;
		free(to_free);
	}
	line = lst->str;
	while (length < lst->length && line[length] == '\n')
		length++;
	lst->length -= length;
	ft_memcpy(line, &(line[length]), lst->length);
	*head = lst;
}

static char	*fgnl_concat_line(t_fgnl_string **head)
{
	size_t					length;
	char					*dst;
	t_fgnl_string			*lst;
	size_t					start;

	length = fgnl_find_line_length(*head);
	dst = ft_strnew(length);
	if (dst == NULL)
		return (NULL);
	start = 0;
	lst = *head;
	while (lst->next)
	{
		ft_memcpy(&(dst[start]), lst->str, lst->length);
		start += lst->length;
		lst = lst->next;
	}
	ft_memcpy(&(dst[start]), lst->str, length - start);
	fgnl_delete_trash(head, length);
	return (dst);
}

static int	reader(int fd, t_fgnl_string *lst)
{
	int							ret;
	int							out;

	if (ft_strnchr(lst->str, '\n', lst->length))
		return (0);
	out = 0;
	if (lst->length == FGNL_BUFF_SIZE)
	{
		lst->next = fgnl_lstnew(NULL, 0);
		lst = lst->next;
	}
	ret = read(fd, &(lst->str[lst->length]), FGNL_BUFF_SIZE - lst->length);
	while (ret > 0)
	{
		out += ret;
		lst->length += (size_t)ret;
		if (ft_strnchr(lst->str, '\n', lst->length))
			return (out);
		lst->next = fgnl_lstnew(NULL, 0);
		if (!(lst->next))
			return (-1);
		lst = lst->next;
		ret = read(fd, &(lst->str[lst->length]), FGNL_BUFF_SIZE - lst->length);
	}
	return (out);
}

/*
**	This function returns text from source line by line. Rest of data
**	stores in heap memory. This data still availiable untill you
**	delete it by function fgnl_head("delete") or you can read this document
**	untill its end. The function is not safety in case of various fd.
*/

int	fgnl(int fd, char **line)
{
	static t_fgnl_string			**head;

	if (!line || fd < 0 || fd > FGNL_FD_MAX)
		return (-1);
	head = fgnl_head(fd, "get");
	if (!(head) || !(*head))
	{
		head = fgnl_head(fd, "create");
		if (!(head) || !(*head))
			return (-1);
	}
	if (reader(fd, *head) < 0)
	{
		fgnl_head(fd, "delete");
		return (-1);
	}
	*line = fgnl_concat_line(head);
	if (!(*line))
	{
		fgnl_head(fd, "delete");
		return (-1);
	}
	return (ft_strlen(*line));
}
