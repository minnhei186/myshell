/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:41:28 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/15 10:41:51 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	builtin_unset(t_prompt_info *info, char **argv)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (item_unset(info->map, argv[i]) < 0)
		{
			printf("error\n");
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	return (status);
}
