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
#include "./libft/includes/libft.h"

/**static ssize_t	save_a_read(const int fd, t_data *data)
{
	ssize_t i;
	char	*cache;
	char	*result;

	if (!data->content)
	{
		if (!(data->content = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
		i = read(fd, &data->content, BUFF_SIZE);
		if (i > 0)
			*((char*)data->content + i) = '\0'; //THIS IS CAUSING A SEGF
	ft_putendl("test");
		return (i);
	}
	if (!(cache = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	i = read(fd, &cache, BUFF_SIZE);
	if (i == 0 || i == -1)
		return (i);
	cache[i] = '\0';
	result = ft_strjoin((char*)data->content, cache);
	free(data->content);
	free(cache);
	data->content = result;
	return (i);
}

static char	*treat_buffer(char *content)
{
	char	*result;
	int		i;
	int		j;

	j = -1;
	i = 0;
	while (content[i] != '\n')
		i++;
	if (!(result = (char*)malloc(sizeof(char) * i)))
		return (NULL);
	while (++j < i)
		result[j] = content[j];
	result[j] = '\0';
	// DONT FORGET TO REMOVE THE I FIRST CHARS FROM CONTENT
	return (result);
}

static int	parse(const int fd, char **line, t_list *list, t_list *before)
{
	t_data	*data;
	int		i;

	i = 1;
	data = (t_data*)list->content;
	while (!ft_strchr(data->content, '\n') && i)
		i = save_a_read(fd, data);
	if (i == 0)
	{
		*line = data->content;
		free(data);
		if (before == list)
			before = before->next;
		else
			before = list->next;
		free(list);
		return (0);
	}
	else if (i == -1)
		return (-1);
	else
	{
		free (*line);
		*line = treat_buffer(data->content);
		return (0);
	}
}**/

static int	create_new_data(const int fd, t_data **data)
{
	t_data		*result;
	size_t		i;

	i = 0;
	if (!*data)
	{
		if (!(*data = (t_data*)malloc(sizeof(t_data))))
			return (-1);
		data[i]->fd = fd;
		data[i]->end = 1;
		return (1);
	}
	result = *data;
	while (data[i++]->end != 1)
		;
	if (!(*data = (t_data*)malloc(sizeof(t_data*) * (i + 1))))
		return (-1);
	ft_putstr("test");
	*data[i].fd = fd;
	*data[i].end = 1;
	ft_putstr("test");
	while (0 < i--)
	{
		data[i]->fd = result[i].fd;
		data[i]->end = 0;
	}
	free(result);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_data	*data = NULL;
	size_t			i;

	i = 0;
	while (data && data[i].end != 1 && data[i].fd != fd)
	 	i++;
	if (!data || data[i++].fd != fd)
		if (!(create_new_data(fd, &data)))
			return (-1);
	ft_putstr("So in data : ");
	ft_putnbr(i);
	ft_putstr(" is the file descriptor :");
	ft_putnbr(data[i].fd);
	ft_putchar('\n');
	*line = NULL;
	return (0);
}
