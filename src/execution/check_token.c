/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:11:04 by ansimonn          #+#    #+#             */
/*   Updated: 2026/07/13 16:05:32 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 *
 * @brief Prints an error message and returns the associated code
 *
 * @param cmd Invalid command written by the user
 * @param msg Error message to print
 * @return Error code associated to 'msg'
 */
static int	print_cmd_error(char *cmd, char *msg)
{
	size_t	size;

	size = ft_strlen(cmd);
	write(2, "goth_in_the_shell: ", 19);
	write(2, cmd, size);
	size = ft_strlen(msg);
	write(2, msg, size);
	if (!ft_strncmp(msg, ": Permission denied\n", 21)
		|| !ft_strncmp(msg, ": Is a directory\n", 18))
		return (126);
	if (!ft_strncmp(msg, ": filename argument required\n", 29))
		return (2);
	if (!ft_strncmp(msg, ": No such file or directory\n", 29))
		return (127);
	return (1);
}

static t_command	*skip_empty_args(t_command *args)
{
	t_command	*new;
	t_command	*node;
	t_command	*tmp;

	if (!args)
		return (NULL);
	new = ft_calloc(1, sizeof(t_command));
	node = new;
	while (args && args->str)
	{
		tmp = args->next;
		if (*args->str)
		{
			node->next = args;
			node = node->next;
		}
		else
		{
			free(args->str);
			free(args);
		}
		args = tmp;
	}
	tmp = new->next;
	free(new);
	return (tmp);
}

/**
 * @brief Checks whether 'str' is a directory or not
 *
 * @param token Token node to check
 * @return 1 if 'str' is a directory, else 0
 */
int	check_tkn(t_token *token)
{
	struct stat	stats;
	int			ret;

	ret = 0;
	token->cmd = skip_empty_args(token->cmd);
	stat(token->cmd->str, &stats);
	if (!ft_strncmp(token->cmd->str, ".", 2))
		ret = print_cmd_error(token->cmd->str,
				": filename argument required\n");
	else if (*token->cmd->str == '/' && S_ISDIR(stats.st_mode))
		ret = print_cmd_error(token->cmd->str, ": Is a directory\n");
	else if ((*token->cmd->str == '/' || (token->cmd->str[0] == '.'
				&& token->cmd->str[1] == '/'))
		&& access(token->cmd->str, F_OK) < 0)
		ret = print_cmd_error(token->cmd->str,
				": No such file or directory\n");
	else if (token->cmd->str[0] == '.' && token->cmd->str[1] == '/'
		&& access(token->cmd->str, X_OK) < 0)
		ret = print_cmd_error(token->cmd->str, ": Permission denied\n");
	return (ret);
}
