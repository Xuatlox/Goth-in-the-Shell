/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:00:30 by mcrenn            #+#    #+#             */
/*   Updated: 2026/05/14 11:43:07 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Function that compare every char of a string with special char and return an int which mean if it's expandable (1) or not (0)
 *
 * @param str The sended argument.
 * @param qte_state A structure which describe the actual "quote state" (simple, double or no quote) of str.
 * @return int
 */
int isExpand(char *str, t_quote_state qte_state)
{
	if ((isalpha(str[0]) || str[0] == '_' || str[0] == '?' || str[0] == '@'
	|| str[0] == '*' || str[0] == '#' || str[0] == '$' || str[0] == '!'
	|| str[0] == '-' || ft_isdigit(str[0])) && qte_state != SIMPLE_QTE)
		return (1);
	return (0);
}

/**
 * @brief Function that recreate the sended string while replacing the expanded word by his valor in the env.
 *
 * @param minishell A structure that contain the token & the env chained list.
 * @param str The string to be replaced.
 * @param i The index where the expanded word start.
 * @return t_status
 */
t_status	expander(t_minishell *minishell, char **str, size_t *i)
{
	char	*new_str;
	char	*envar;
	char	*var;

	envar = make_env_var(*str + *i + 1);
	if (!envar)
		return	(ALLOCATION_FAILURE);
	var = make_env_val(minishell, envar);
	new_str = ft_calloc(ft_strlen(*str) - ft_strlen(envar) + ft_strlen(var), 1);
	if (!new_str)
	{
		free(envar);
		return (ALLOCATION_FAILURE);
	}
	ft_strlcpy(new_str, *str, *i + 1);
	ft_strlcat(new_str, var, ft_strlen(var) + ft_strlen(new_str) + 1);
	ft_strlcat(new_str, *str + *i + 1 + ft_strlen(envar), ft_strlen(*str) - ft_strlen(envar) + ft_strlen(var) + 1);
	free(envar);
	free(*str);
	*str = new_str;
	*i += ft_strlen(var);
	free(var);
	return (SUCCESS);
}




/**
 * @brief Function that check for each argument if the managing of the quote is valid,  it start by '$' and if it's expandable. If all conditions are met, it calling expander which expand the argument.
 *
 * @param minishell A structure that contain the token & the env chained list.
 * @param status An enum which describe if the actual operation is valid (SUCCESS), or not (FAILURE, [...]).
 */
void	expand(t_minishell *minishell, t_status *status)
{
	size_t			i;
	t_command		*current_cmd;
	t_token			*tkn_node;
	t_quote_state	qte_state;

	tkn_node = minishell->tkn_node;
	while (tkn_node)
	{
		current_cmd = tkn_node->cmd;
		while (current_cmd)
		{
			qte_state = NO_QTE;
			i = 0;
			while (current_cmd->str && current_cmd->str[i])
			{
				check_quotes(current_cmd->str[i], &qte_state);
				// printf("QTE_STATE: %d\n", qte_state);
				// printf("EXP: %d\n", isExpand(current_cmd->str + i, qte_state));
				// printf("STR: %s\n", current_cmd->str + i);
				if (current_cmd->str[i] == '$' && isExpand(current_cmd->str + i, qte_state) == 1)
					*status = expander(minishell, &current_cmd->str, &i);
				else
					i++;
				if (*status)
					return ;
			}
			current_cmd = current_cmd->next;
		}
		tkn_node = tkn_node->next;
	}
}
