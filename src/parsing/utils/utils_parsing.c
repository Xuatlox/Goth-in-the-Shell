/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 06:45:16 by mcrenn            #+#    #+#             */
/*   Updated: 2026/06/03 11:05:07 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	charjoin(t_command *src, char c)
{
	char	*tmp;
	size_t	size;

	if (!c || !src)
		return (SUCCESS);
	if (!src->str)
		size = 2;
	else
		size = ft_strlen(src->str) + 2;
	tmp = ft_calloc(size, 1);
	if (!tmp)
		return (ALLOCATION_FAILURE);
	if (src->str)
		ft_strlcat(tmp, src->str, size - 1);
	ft_strlcat(tmp, &c, size);
	if (src->str)
		free(src->str);
	src->str = tmp;
	return (SUCCESS);
}

t_status	str_charjoin(char **src, char c)
{
	char	*tmp;
	size_t	size;

	if (!c || !src)
		return (SUCCESS);
	if (!*src)
		size = 2;
	else
		size = ft_strlen(*src) + 2;
	tmp = ft_calloc(size, 1);
	if (!tmp)
		return (ALLOCATION_FAILURE);
	if (*src)
		ft_strlcat(tmp, *src, size - 1);
	ft_strlcat(tmp, &c, size);
	if (*src)
		free(*src);
	*src = tmp;
	return (SUCCESS);
}
