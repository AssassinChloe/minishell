/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:45:39 by vmercier          #+#    #+#             */
/*   Updated: 2021/06/04 13:59:12 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;
	size_t	ret;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (!size)
		return (src_len);
	if (size < dest_len + 1)
		return (size + src_len);
	else
		ret = src_len + dest_len;
	i = 0;
	while (src[i] && (i + dest_len) < (size - 1))
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	dest[i + dest_len] = '\0';
	return (ret);
}
