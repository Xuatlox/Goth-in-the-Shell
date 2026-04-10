/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:00:25 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/09 19:05:05 by xuatlox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void	dispatch(t_command *cmd, int fd_in, int fd_out, t_env *env)
{
	if (!ft_strncmp(cmd->str, "cd", 3))
		exec_cd(cmd->next, fd_out, env);
	if (!ft_strncmp(cmd->str, "export", 7))
		exec_export(cmd->next, fd_out, env);
	if (!ft_strncmp(cmd->str, "pwd", 4))
		exec_pwd(cmd->next, fd_out, env);
	exec_child(cmd, fd_in, fd_out);
}

int	execute(const t_token *tokens, t_env *env)
{
	while (tokens)
	{
		dispatch(tokens->str, tokens->infile, tokens->outfile, env);
		tokens = tokens->next;
	}
}

// int	main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (0);
// 	printf("%d\n", is_builtin(av[1]));
// }
