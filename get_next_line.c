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
#include "libft/includes/libft.h"

static void	ft_lstremovecontent(t_list **listadd, void *content)
{
	t_list	*cache;
	t_list	*tmp;
	t_list	*list;

	list = *listadd;
	cache = list->next;
	while (list->content == content)
	{
		free(list);
		list = cache;
		cache = list->next;
	}
	tmp = list;
	while (cache)
	{
		if (cache->content == content)
		{
			tmp->next = cache->next;
			free(cache);
			cache = tmp->next;
		}	
		tmp = cache;
		cache = cache->next;
	}
	listadd = &list;
	ft_putstr("---DEBUG---\n");
	t_data	*data;
	while (list)
	{
		data = (t_data*)list->content;
		ft_putstr("fd : ");
		ft_putnbr(data->fd);
		ft_putendl("");
		list = list->next;
	}
}

static int	parse(t_list *list, t_data *data, char **line)
{
	int		i;

	i = 0;
	while ((!data->content || !ft_strchr(data->content, '\n')) && i)
	{
		i = 0;
		//i = save_a_read(data->fd, data->content);
	}
	if (i == -1 || i == 0)
	{
		ft_putstr("congratulation, the data of the fd : ");
		ft_putnbr(data->fd);
		ft_putendl(" is now deleted.");
		*line = data->content;
		free(data->content);
		ft_lstremovecontent(&list, (void*)data); //test if it work
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
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (-1);
	data->fd = fd;
	data->content = NULL;
	cache = ft_lstnew((void*)data, sizeof(data));
	ft_lstadd(&list, cache);
	ft_putstr("We just created a t_list elemn for the fd : ");
	ft_putnbr(data->fd);
	ft_putendl("");
	return (parse(list, data, line));
}
