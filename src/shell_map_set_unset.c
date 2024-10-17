/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_map_set_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:48:45 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/17 22:32:52 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	item_set(t_map *map, const char *name, const char *value)
{
	t_item	*new_item;
	t_item	*old_item;
	t_item	*last_item;

	old_item = map->item;
	last_item = NULL;
	new_item = make_unit_item(name, value);
	while (old_item != NULL)
	{
		if (ft_strcmp(name, old_item->name) == 0)
		{
			free(old_item->value);
			old_item->value = NULL;
			old_item->value = minishell_strdup(value);
			item_free(new_item);
			return ;
		}
		last_item = old_item;
		old_item = old_item->next;
	}
	if (last_item == NULL)
		map->item = new_item;
	else
		last_item->next = new_item;
}

int	item_unset(t_map *map, const char *name)
{
	t_item	*item;
	t_item	*prev;

	item = map->item;
	prev = NULL;
	while (item != NULL)
	{
		if (ft_strcmp(item->name, name) == 0)
		{
			if (prev == NULL)
			{
				free(item->name);
				free(item->value);
				free(item);
				item = NULL;
			}
			else
			{
				prev->next = item->next;
				free(item->name);
				free(item->value);
				free(item);
			}
			return (1);
		}
		prev = item;
		item = item->next;
	}
	return (1);
}

void	item_put(t_prompt_info *info, t_map *map, const char *string,
		bool empty_value)
{
	char	*middle_qual;
	char	*name;
	char	*value;

	middle_qual = ft_strchr(string, '=');
	if (middle_qual == NULL)
	{
		if (empty_value == false)
		{
			minishell_yourser_perror(info, "need = in environ");
			return ;
		}
		else
		{
			name = minishell_strdup(string);
			value = NULL;
		}
	}
	else
	{
		name = minishell_strndup(string, middle_qual - string);
		value = minishell_strdup(middle_qual + 1);
	}
	item_set(map, name, value);
	free(name);
	free(value);
}
