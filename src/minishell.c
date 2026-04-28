/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/28 10:38:02 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	sig_ind = 0;

int	main(void)
{
	char		*line;
	int			i;
	t_status	status;
	t_token		*tkn_node;

	status = SUCCESS;
	i = 0;
	while (i != 5)
	{
		line = readline("Write input: ");
		if (line[0] != 0)
			add_history(line);
		tkn_node = parsing(line, &status);
		lst_clear_tkn(&tkn_node);
		i++;
	}
	rl_clear_history();
}
