/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 06:45:16 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/17 14:53:01 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redirect	check_redirect(char *str)
{
	int	i;
	t_redirect redirect;

	i = 0;
	if (str[i + 1] && str[i] == '<' && str[i + 1] == '<')
		redirect = HEREDOC;
	else if (str[i + 1] && str[i] == '>' && str[i + 1] == '>')
		redirect = APPEND;
	else if (str[i] == '<')
		redirect = INPUT;
	else if (str[i] == '>')
		redirect = TRUNC;
	else
		redirect = NONE;
	return (redirect);
}

void	check_quotes(char c, t_quote_state *quote_state)
{
	if (c == '\'')
	{
		if (*quote_state == NO_QTE)
			*quote_state = SIMPLE_QTE;
		else if (*quote_state == SIMPLE_QTE)
			*quote_state = NO_QTE;
	}
	else if (c == '\"')
	{
		if (*quote_state == NO_QTE)
			*quote_state = DOUBLE_QTE;
		else if (*quote_state == DOUBLE_QTE)
			*quote_state = NO_QTE;
	}
}

t_status	charjoin(t_command *src, char c)
{
	char	*tmp;
	size_t		size;

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


