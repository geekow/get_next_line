/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 19:35:13 by jjacobi           #+#    #+#             */
/*   Updated: 2016/11/29 19:44:38 by jjacobi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static void	ft_lstremovecontent(t_list **list, void *content)
{
	t_list	*cache;
	t_list	*tmp;

	cache = *list->next;
	if (*list->content == content)
	{
		free(list);
		*list = cache;
	}
	while (cache)
	{

		cache = cache->next;
	}
		
	cache = *list;
}

static int	parse(t_list *list, t_data *data, char **line)
{
	char	buf[BUFF_SIZE];
	int		i;

	i = 0;
	while (!ft_strchr(data->content, '\n') && i)
		i = save_a_read(fd, data->content);
	if (i == -1 || i == 0)
	{
		*line = data->content;
		free(data->content);
		/** FREE LIST ELEM CODE FT_LSTREMOVECONTENT **/
		return (i);
	}
	/** RETURN THE FIRST X CHARS TO THE /n **/
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*list;
	t_list			*cache;
	t_data			*data;

	cache = list;
	while (cache)
	{
		data = (t_data*)cache->content;
		if (data->fd == fd)
			return (parse(list, data, line));
		cache = cache->next;
	}
	if (!(data = malloc(sizeof(t_data))))
		return (-1);
	data->fd = fd;
	data->content = NULL;
	cache = ft_lstnew((void*)data, sizeof(data));
	ft_lstadd(&list, cache);
	return (parse(list, data, line));
}
