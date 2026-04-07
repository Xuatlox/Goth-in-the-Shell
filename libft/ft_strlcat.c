/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:25:25 by ansimonn          #+#    #+#             */
/*   Updated: 2025/10/29 11:17:53 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len + size);
	dst_len = ft_strlen(dst);
	if (dst_len > size - 1)
		return (src_len + size);
	i = -1;
	while (src[++i] && i + dst_len < size - 1)
		dst[i + dst_len] = src[i];
	dst[i + dst_len] = 0;
	return (dst_len + src_len);
}
