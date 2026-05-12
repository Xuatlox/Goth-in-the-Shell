/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:25:25 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/07 14:02:41 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	if (!dst || !src)
		return (0);
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
