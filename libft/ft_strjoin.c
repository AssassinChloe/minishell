/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:06:08 by cassassi          #+#    #+#             */
/*   Updated: 2020/11/30 12:34:15 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*s3;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + (ft_strlen(s2)) + 1));
	if (!(s3))
		return (NULL);
	while (s1[i])
	{
		s3[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		s3[j] = s2[i];
		i++;
		j++;
	}
	s3[j] = '\0';
	return (s3);
}
