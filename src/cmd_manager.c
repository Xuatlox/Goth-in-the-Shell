/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:45:23 by ansimonn          #+#    #+#             */
/*   Updated: 2026/04/22 16:54:38 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int	get_cmd_size(const t_command *cmd)
{
	int	size;

	size = 0;
	while (cmd)
	{
		++size;
		cmd = cmd->next;
	}
	return (size);
}
