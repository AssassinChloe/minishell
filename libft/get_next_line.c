/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:54:27 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/10 17:42:49 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_check_nl(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	gnl_read_file(int fd, char **file)
{
	int		ret;
	char	save[BUFFER_SIZE + 1];

	ret = 1;
	if (!(*file))
	{
		(*file) = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!(*file))
			return (-2);
		ret = read(fd, (*file), BUFFER_SIZE);
		if (ret == -1)
			return (ret);
		(*file)[ret] = '\0';
	}
	while (gnl_check_nl(*file) == 0 && ret != 0)
	{
		ret = read(fd, save, BUFFER_SIZE);
		if (ret == -1)
			return (ret);
		save[ret] = '\0';
		if (gnl_strjoin(file, save) == -1)
			return (-1);
	}
	return (ret);
}

int	gnl_write_line(char **file, char **line)
{
	int	i;

	i = 0;
	while ((*file)[i] != '\n' && (*file)[i])
		i++;
	(*line) = malloc(sizeof(char) * i + 1);
	if (!(*line))
		return (-1);
	i = 0;
	while ((*file)[i] && (*file)[i] != '\n')
	{
		(*line)[i] = (*file)[i];
		i++;
	}
	(*line)[i] = '\0';
	if (gnl_strtrim(file, line) == -1)
		return (-1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*file = NULL;
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 1 || !(line))
		return (-1);
	ret = gnl_read_file(fd, &file);
	if (ret == -1)
	{
		free(file);
		file = NULL;
		return (-1);
	}
	if (ret == -2)
		return (-1);
	if (gnl_write_line(&file, line) == -1)
	{
		free(file);
		file = NULL;
		return (-1);
	}
	if (ret > 0 || gnl_check_nl(file) == 1)
		return (1);
	free(file);
	file = NULL;
	return (0);
}
