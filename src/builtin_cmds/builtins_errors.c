/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:59:11 by ansimonn          #+#    #+#             */
/*   Updated: 2026/06/02 12:59:32 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Displays an error message if an 'export' argument is incorrect
 *
 * @param str Argument given after the 'export' command
 */
void	print_error_export(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	write(2, "goth_in_the_shell: export: `", 28);
	write(2, str, size);
	write(2, "': not a valid identifier\n", 26);
}
