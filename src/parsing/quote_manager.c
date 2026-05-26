/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:52:52 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/26 15:49:29 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_quotes(char c, t_quote_state *quote_state)
{
	if (c == '\'')
	{
		if (*quote_state == NO_QTE)
			*quote_state = SIMPLE_QTE;
		else if (*quote_state == SIMPLE_QTE)
			*quote_state = NO_QTE;
		else if (*quote_state == DOUBLE_QTE)
			return (0);
		return (1);
	}
	else if (c == '\"')
	{
		if (*quote_state == NO_QTE)
			*quote_state = DOUBLE_QTE;
		else if (*quote_state == DOUBLE_QTE)
			*quote_state = NO_QTE;
		else if (*quote_state == SIMPLE_QTE)
			return (0);
		return (1);
	}
	return (0);
}

static size_t	quote_counter(char *cmd)
{
	size_t			i;
	size_t			qte_counter;
	t_quote_state	qte_state;

	i = 0;
	qte_counter = 0;
	while (cmd[i])
	{
		if (check_quotes(cmd[i], &qte_state) == 1)
			qte_counter++;
		i++;
	}
	return (qte_counter);
}

static t_status	str_without_qte(char **str, size_t qte_nb)
{
	char			*new_str;
	t_quote_state	qte_state;
	size_t			i;
	size_t			j;

	i= 0;
	j = 0;
	qte_state = NO_QTE;
	new_str = ft_calloc(ft_strlen(*str) - qte_nb + 1, 1);
	if (!new_str)
		return (ALLOCATION_FAILURE);
	while ((*str)[i])
	{
		if (check_quotes((*str)[i], &qte_state) == 0)
		{
			new_str[j] = (*str)[i];
			j++;
		}
		i++;
	}
	free(*str);
	*str = new_str;
	return (SUCCESS);
}

void	remove_quotes(t_token *tkn_node, t_status *status)
{
	size_t			qte_counter;
	t_command		*current_cmd;

	while (tkn_node)
	{
		current_cmd = tkn_node->cmd;
		while (current_cmd)
		{
			qte_counter = quote_counter(current_cmd->str);
			if (qte_counter)
				*status = str_without_qte(&current_cmd->str, qte_counter);
			if (*status)
				return ;
			current_cmd = current_cmd->next;
		}
		tkn_node = tkn_node->next;
	}
}
