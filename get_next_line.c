/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 19:35:13 by jjacobi           #+#    #+#             */
/*   Updated: 2016/11/25 17:30:37 by jjacobi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int	linelen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	if (!str[i])
		return (i);
	return (-1);
}

static int	parse(const int fd, char **line, t_list *list)
{
	char	buf[BUFF_SIZE];
	t_list	*cache;
	ssize_t	tmp;
	t_data	*data;

	data = (t_data*)list->content;
	if (!(data->result = malloc(sizeof(char) * data->index))) /** TODO: try without malloc **/
			return (-1);
	if ((read(fd, &result, data->index)) == -1)
		return (-1);
	free(result);
	if (BUFF_SIZE == (tmp = read(fd, &buf, BUFF_SIZE)))
	{
		data->result = (void*)ft_strdup(buf);
		while ((tmp = linelen(buf)) == -1)
		{
			if (read(fd, &buf, BUFF_SIZE) == BUFF_SIZE)
				data->result = ft_strjoin((char*)data->result, buf);
			/** if they is no more '\n' but a EOF you have to delete list elem and return 0 **/
		}
		*line = (char*)data->result;
	}
	else if (tmp != -1)
	{
		*line = ft_strdup(buf);
		cache = list->next;
		ft_lstdelone(&list, del*);		/** TODO : add del function**/
		list = cache;
		return (0);
	}
	else
		return (-1);
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
			return (parse(fd, line, cache));
		cache = cache->next;
	}
	if (!(data = malloc(sizeof(t_data))))
		return (-1);
	data->fd = fd;
	data->index = 0;
	cache = ft_lstnew((void*)data, sizeof(data));
	ft_lstadd(&list, cache);
	return (parse(fd, line, cache));
}
