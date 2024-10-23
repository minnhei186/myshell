/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:42:35 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 13:31:49 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	print_all_env(t_prompt_info *info)
{
	t_item	*item;

	item = info->map->item;
	while (item != NULL)
	{
		if (item->value)
		{
			printf("declare -x %s=\"%s\"\n", item->name, item->value);
		}
		else
		{
			printf("declare -x %s\n", item->name);
		}
		item = item->next;
	}
}

int	builtin_export(t_prompt_info *info, char **argv)
{
	size_t	i;
	int		status;

	if (argv[1] == NULL)
	{
		print_all_env(info);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		item_put(info, info->map, argv[i], 1);
		if (info->yourser_err == 1)
		{
			minishell_yourser_perror(info, "faild to export");
			status = 1;
		}
		i++;
	}
	return (status);
}
