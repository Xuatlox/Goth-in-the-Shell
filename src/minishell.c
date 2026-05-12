/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:07:18 by ansimonn          #+#    #+#             */
/*   Updated: 2026/05/10 14:54:03 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_ind = 0;

int	main(int argc, char **argv)
{
	char		*line;
	t_status	status;
	t_token		*tkn_node;
	t_env		*env;
	char		*name;
	char		*val;

	env = malloc(sizeof(t_env));
	val = calloc(5, 1);
	name = calloc(5, 1);
	ft_strlcpy(val, "titi", 5);
	ft_strlcpy(name, "TOTO", 5);
	env->next = NULL;
	env->val = val;
	env->name = name;
	(void)argc;
	(void)argv;
	status = SUCCESS;
	while (1)
	{
		line = readline("Write input: ");
		if (line[0] != 0)
			add_history(line);
		tkn_node = parsing(line, &status, env);
		lst_clear_tkn(&tkn_node);// Ephemere
	}
	rl_clear_history();
}
