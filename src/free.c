/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:32:27 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/16 16:32:54 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	item_free(t_item *item)
{
	t_item	*next_item;

	while (item != NULL)
	{
		if (item->name)
		{
			free(item->name);
			item->name = NULL;
		}
		if (item->value)
		{
			free(item->value);
			item->value = NULL;
		}
		next_item = item->next;
		item->next = NULL;
		free(item);
		item = next_item;
	}
}

void	ppt_free(char **ppt)
{
	int	i;

	if (ppt == NULL)
		return ;
	i = 0;
	while (ppt[i])
	{
		free(ppt[i]);
		ppt[i] = NULL;
		i++;
	}
	free(ppt);
}

void	map_free(t_map *map)
{
	if (map->item)
	{
		item_free(map->item);
		map->item = NULL;
	}
	if (map->envp)
	{
		ppt_free(map->envp);
		map->envp = NULL;
	}
}

void	clear_info(t_prompt_info *info)
{
	if (info->str)
	{
		free(info->str);
		info->str = NULL;
	}
	if (info->map)
	{
		map_free(info->map);
		free(info->map);
		info->map = NULL;
	}
}
