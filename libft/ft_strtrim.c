/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:43:59 by ansimonn          #+#    #+#             */
/*   Updated: 2025/10/28 11:00:51 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reduce(char const *s1, int *start, int *end, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1[*start])
		{
			(*start)++;
			i = 0;
		}
		else if (set[i] == s1[*end])
		{
			(*end)--;
			i = 0;
		}
		else
			i++;
	}
}

static char	*trim(char const *s1, int const start, int const end)
{
	char	*res;
	int		i;

	i = 0;
	if (start > end)
		res = ft_calloc(1, sizeof(char));
	else
		res = ft_calloc(end - start + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (start + i <= end)
	{
		res[i] = s1[start + i];
		i++;
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	reduce(s1, &start, &end, set);
	res = trim(s1, start, end);
	return (res);
}
