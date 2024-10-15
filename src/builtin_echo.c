/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:40:44 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/15 10:40:54 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	builtin_echo(t_prompt_info *info, char **argv)
{
	size_t	i;
	int		new_line_flag;
	int		first_flag;

	(void)info;
	i = 1;
	new_line_flag = 1;
	if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		i++;
		new_line_flag = 0;
	}
	first_flag = 1;
	while (argv[i])
	{
		if (first_flag == 0)
			write(STDOUT_FILENO, " ", 1);
		first_flag = 0;
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
	}
	if (new_line_flag == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
