/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:59:08 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/10 17:44:35 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	gnl_strtrim(char **file, char **line)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(sizeof(char) * gnl_strlen(*file) - gnl_strlen(*line) + 1);
	if (!tmp)
		return (-1);
	i = 0;
	while ((*file)[i] == (*line)[i] && (*file)[i] && (*line)[i])
		i++;
	if ((*file)[i] == '\n')
		i++;
	j = 0;
	while ((*file)[i])
		tmp[j++] = (*file)[i++];
	tmp[j] = '\0';
	free(*file);
	(*file) = gnl_strdup(tmp);
	free(tmp);
	tmp = NULL;
	if (!(*file))
		return (-1);
	return (0);
}

int	gnl_strjoin(char **file, char *save)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * gnl_strlen(*file) + BUFFER_SIZE + 1);
	if (!tmp)
		return (-1);
	while ((*file)[i])
	{
		tmp[i] = (*file)[i];
		i++;
	}
	while (save[j])
		tmp[i++] = save[j++];
	tmp[i] = '\0';
	free(*file);
	(*file) = gnl_strdup(tmp);
	free(tmp);
	tmp = NULL;
	if (!(*file))
		return (-1);
	return (0);
}

char	*gnl_strdup(char *str)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc(sizeof(char) * gnl_strlen(str) + 1);
	if (!(copy))
		return (NULL);
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
