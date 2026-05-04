/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/04 14:18:51 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	sig_ind = 0;

int	main(int argc, char **argv/* , char **envp */)
{
	char		*line;
	int			i;
	t_status	status;
	t_token		*tkn_node;

	(void)argc;
	(void)argv;
	status = SUCCESS;
	i = 0;
	while (i != 5)
	{
		line = readline("Write input: ");
		if (line[0] != 0)
			add_history(line);
		tkn_node = parsing(line, &status/* , envp */);
		lst_clear_tkn(&tkn_node);// Ephemere
		i++;
	}
	rl_clear_history();
}
