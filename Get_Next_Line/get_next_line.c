/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdi-paol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:50:56 by mdi-paol          #+#    #+#             */
/*   Updated: 2023/05/12 16:23:35 by mdi-paol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_return_line(char *storage)
{
	int	i;

	i = 0;
	while (storage[i])
	{
		if (storage[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_line_wow(char *tmp)
{
	char	*line;
	int		i;

	i = 0;
	if (tmp[i] == 0 || !tmp)
		return (NULL);
	while (tmp[i] != '\n' && tmp[i])
	{
		i++;
	}
	line = (char *)ft_calloc(sizeof(char) * (i + 2), 1);
	while (i >= 0)
	{
		line[i] = tmp[i];
		i--;
	}
	return (line);
}

char	*update_storage(char *storage)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (storage[i] != '\n' && storage[i])
		i++;
	if (storage[i] == '\n' && storage[i])
		i++;
	if (!storage[i])
	{
		free (storage);
		return (NULL);
	}
	tmp = ft_calloc(sizeof (char), (ft_ssstrlen(storage) - i + 1));
	while (storage[i])
	{
		tmp[j] = storage[i];
		j++;
		i++;
	}
	free (storage);
	return (tmp);
}

char	*search_return_line(char *storage, int fd)
{
	int		reading;
	char	*buffer;

	reading = 1;
	while (!check_return_line(storage) && reading > 0)
	{
		buffer = (char *)ft_calloc(sizeof (char) * BUFFER_SIZE + 1, 1);
		reading = read (fd, buffer, BUFFER_SIZE);
		if (reading == -1)
		{
			free (buffer);
			free (storage);
			return (NULL);
		}
		if (reading == 0)
		{
			free (buffer);
			return (storage);
		}
		storage = ft_strrjoin(storage, buffer);
		free (buffer);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage)
		storage = (char *)ft_calloc(sizeof (char), 1);
	storage = search_return_line(storage, fd);
	if (!storage)
		return (NULL);
	tmp = get_line_wow (storage);
	storage = update_storage(storage);
	return (tmp);
}
