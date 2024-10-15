/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:43:45 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/15 10:44:27 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	builtin_env(t_prompt_info *info)
{
	t_item	*item;

	item = info->map->item;
	while (item != NULL)
	{
		if (item->value)
			printf("%s=%s\n", item->name, item->value);
		item = item->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}
