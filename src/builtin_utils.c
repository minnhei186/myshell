/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:16:13 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 13:20:11 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	is_numeric(char *s)
{
	if (!ft_isdigit(*s))
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

void	set_builtin_commands(char *builtin_commands[BUILTIN_SIZE])
{
	builtin_commands[0] = "exit";
	builtin_commands[1] = "env";
	builtin_commands[2] = "export";
	builtin_commands[3] = "unset";
	builtin_commands[4] = "echo";
	builtin_commands[5] = "pwd";
	builtin_commands[6] = "cd";
}
