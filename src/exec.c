/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:00:25 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/08 16:12:33 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void	dispatch(t_command *str, int fd_in, int fd_out, t_env *env)
{
	if (!ft_strncmp(str->str, "cd", 3))
		exec_cd(str, fd_out, env);
	if (!ft_strncmp(str->str, "export", 7))
		exec_export(str, fd_out);
	if (!ft_strncmp(str->str, "unset", 6))
		exec_unset(str, fd_out);
	if (!ft_strncmp(str->str, "exit", 5))
		exec_exit(str, fd_out);
	exec_child(str, fd_in, fd_out);
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
