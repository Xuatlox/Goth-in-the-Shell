/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/16 17:14:17 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char		*line;
	int			i;
	t_status	status;
	t_token		*lex;

	status = SUCCESS;
	i = 0;
	while (i != 5)
	{
		line = readline("Write input: ");
		lex = lexer(line, &status);
		while (lex)
		{
			printf("New Node:\n");
			while (lex->cmd)
			{
				printf("CMD: %s\n", lex->cmd->str);
				lex->cmd = lex->cmd->next;
			}
			lex = lex->next;
		}
		if (line[0] != 0)
			add_history(line);
		//parsing(lex);
		i++;
	}
	rl_clear_history();
}
