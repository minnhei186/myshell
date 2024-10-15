/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:45:14 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/15 10:45:29 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	builtin_exit(t_prompt_info *info, char **argv)
{
	long	res;
	char	*arg;
	char	*endptr;

	if (argv[1] == NULL)
		exit(info->last_status);
	if (argv[2])
	{
		return (1);
	}
	arg = argv[1];
	if (is_numeric(arg))
	{
		errno = 0;
		res = strtol(arg, &endptr, 10);
		if (errno == 0 && *endptr == '\0')
			exit((int)res);
	}
	exit(255);
}
