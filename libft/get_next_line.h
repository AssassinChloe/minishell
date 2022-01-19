/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:01:58 by cassassi          #+#    #+#             */
/*   Updated: 2021/02/11 23:46:08 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdlib.h>
# include <unistd.h>

int		gnl_strlen(char *str);
int		gnl_strtrim(char **file, char **line);
int		gnl_strjoin(char **file, char *save);
char	*gnl_strdup(char *str);
int		gnl_check_nl(char *file);
int		gnl_read_file(int fd, char **file);
int		gnl_write_line(char **file, char **line);
int		get_next_line(int fd, char **line);

#endif
