/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:00:25 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/08 15:09:20 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void	dispatch(t_command *str, int fd_in, int fd_out)
{
	if (!ft_strncmp(str->cmd, "cd", 3))
		exec_cd(str);
	if (!ft_strncmp(str->cmd, "export", 7))
		exec_export(str);
	if (!ft_strncmp(str->cmd, "unset", 6))
		exec_unset(str);
	if (!ft_strncmp(str->cmd, "exit", 5))
		exec_exit(str);
	exec_child(str);
}

int	execute(const t_token *tokens)
{
	while (tokens)
	{
		dispatch(tokens->str, tokens->infile, tokens->outfile);
		tokens = tokens->next;
	}
}

// int	main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (0);
// 	printf("%d\n", is_builtin(av[1]));
// }
