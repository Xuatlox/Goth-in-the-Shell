/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:00:30 by mcrenn            #+#    #+#             */
/*   Updated: 2026/06/10 16:32:57 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function that compare every char of a string with special char and return an int which mean if it's expandable (1) or not (0)
 *
 * @param str The sended argument.
 * @param qte_state A structure which describe the actual "quote state" (simple, double or no quote) of str.
 * @return int
 */
int isExpand(char *str, t_quote_state qte_state)
{
	if ((ft_isalpha(str[0]) || str[0] == '_' || str[0] == '?' || str[0] == '@'
	|| str[0] == '*' || str[0] == '#' || str[0] == '$' || str[0] == '!'
	|| str[0] == '-' || (str[0] == '"' && qte_state == NO_QTE)
	|| (str[0] == '\'' && qte_state == NO_QTE)
	|| ft_isdigit(str[0])) && qte_state != SIMPLE_QTE)
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

t_command *lst_word(char* cmd, t_status *status)
{
	size_t			i;
	t_token			*tkn_node;
	t_quote_state	quote_state;
	t_command		*cmd_word;

	i = 0;
	quote_state = NO_QTE;
	tkn_node = lst_newtoken(status);
	cmd_word = NULL;
	while (cmd && cmd[i++] && *status == SUCCESS)
	{
		check_quotes(cmd[i - 1], &quote_state);
		if (ft_isspace(cmd[i - 1]) == 1
			&& quote_state == NO_QTE && *status == SUCCESS)
			ft_lstadd_command(tkn_node, 0, status);
		else
			ft_lstadd_command(tkn_node, cmd[i - 1], status);
	}
	if (*status == SUCCESS)
		cmd_word = tkn_node->cmd;
	else
		lst_clear_cmd(&tkn_node->cmd);
	if (tkn_node)
		free(tkn_node);
	return (cmd_word);
}

void	lst_add_word(t_command **current_cmd, t_status *status)
{
	t_command	*new_lst_cmd;
	t_command	*stock_next;


	new_lst_cmd = lst_word((*current_cmd)->str, status);
	if (*status || !new_lst_cmd)
		return ;
	stock_next = (*current_cmd)->next;
	free((*current_cmd)->str);
	(*current_cmd)->str = new_lst_cmd->str;
	(*current_cmd)->next = new_lst_cmd->next;
	free(new_lst_cmd);
	*current_cmd = ft_lstlast_command(*current_cmd);
	(*current_cmd)->next = stock_next;
}


int	check_expand(char **cmd, t_minishell *shell, t_status *status, t_expand ex)
{
	t_quote_state	qte_state;
	size_t			i;
	int				is_expand;

	is_expand = 0;
	qte_state = NO_QTE;
	i = 0;
	while (cmd && (*cmd)[i])
	{
		check_quotes((*cmd)[i], &qte_state);
		if ((*cmd)[i] == '$' && isExpand(*cmd + i + 1, qte_state) == 1
			&& ex == EXPAND)
		{
			*status = expander(shell, cmd, &i);
			is_expand = 1;
		}
		else
			i++;
		if (*status)
			return (0);
	}
	return (is_expand);
}

/**
 * @brief Function that check for each argument
 * if the managing of the quote is valid,
 * it start by '$' and if it's expandable.
 * If all conditions are met, it calling expander which expand the argument.
 *
 * @param minishell A structure that contain the token & the env chained list.
 * @param status An enum which describe if the actual operation
 * is valid (SUCCESS), or not (FAILURE, [...]).
 */
void	expand(t_minishell *minishell, t_status *status)
{

	t_command		*current_cmd;
	t_token			*tkn_node;

	tkn_node = minishell->tkn_node;
	while (tkn_node && !*status)
	{
		current_cmd = tkn_node->cmd;
		while (current_cmd && !*status)
		{
			if (check_expand(&current_cmd->str, minishell, status, 0) == 1)
				lst_add_word(&current_cmd, status);
			current_cmd = current_cmd->next;
		}
		tkn_node = tkn_node->next;
	}
}
