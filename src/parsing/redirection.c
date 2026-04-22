/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:32:59 by mcrenn            #+#    #+#             */
/*   Updated: 2026/04/22 14:47:56 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	redirect_outfile(t_token *tkn_node, t_status *status, t_redirect redir, char *file_name)
{
	if (tkn_node->outfile != -1)
		close(tkn_node->outfile);
	if (redir == TRUNC)
	{
		tkn_node->outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tkn_node->outfile == -1)
		{
			*status = FAILURE;
			return ;
		}
	}
	if (redir == APPEND)
	{
		tkn_node->outfile = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tkn_node->outfile == -1)
		{
			*status = FAILURE;
			return ;
		}
	}

}

static void	redirect_infile(t_token *tkn_node, t_status *status, t_redirect redir, char *file_name)
{
	if (tkn_node->infile != -1)
		close(tkn_node->infile);
	if (redir == INPUT)
	{
		tkn_node->infile = open(file_name, O_RDONLY);
		if (tkn_node->infile == -1)
		{
			*status = FAILURE;
			return ;
		}
	}
	//if (redir == HEREDOC) //#TODO
}

void	redirect_manager(char *str, t_token *tkn_node, t_status *status, size_t *i)
{
	t_redirect	redir_state;
	char		*new_word;

	new_word = NULL;
	redir_state = check_redirect(&str[*i]);
	if (redir_state == HEREDOC || redir_state == APPEND)
		(*i)++;
	(*i)++;
	while (str[*i] && ft_isspace(str[*i]) == 1 && *status == SUCCESS)
		(*i)++;
	while (str[*i] && *status == SUCCESS && ft_isspace(str[*i]) == 0)
	{
		str_charjoin(&new_word, str[*i]);
		(*i)++;
	}
	if (redir_state == INPUT || redir_state == HEREDOC)
		redirect_infile(tkn_node, status, redir_state, new_word);
	else
		redirect_outfile(tkn_node, status, redir_state, new_word);
	free(new_word);
}
