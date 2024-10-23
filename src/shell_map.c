/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:19:34 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 18:51:46 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	is_identifier(const char *s)
{
	if (is_alpha_or_under(*s) == false)
		return (false);
	s++;
	while (*s)
	{
		if (is_alpha_or_under_or_digit(*s) == false)
			return (false);
		s++;
	}
	return (true);
}

t_item	*make_unit_item(const char *name, const char *value)
{
	t_item	*new_item;

	new_item = (t_item *)minishell_malloc(sizeof(t_item));
	new_item->name = (char *)minishell_strdup(name);
	new_item->value = (char *)minishell_strdup(value);
	new_item->next = NULL;
	return (new_item);
}

t_map	*minishell_make_map(void)
{
	t_map	*new_map;

	new_map = (t_map *)minishell_malloc(sizeof(t_map));
	new_map->item = NULL;
	new_map->envp = NULL;
	return (new_map);
}

char	*search_value(t_item *item, const char *find_name)
{
	char	*new_value;

	if (ft_strncmp(item->name, find_name, ft_strlen(find_name)) == 0)
	{
		new_value = minishell_strdup(item->value);
		return (new_value);
	}
	return (NULL);
}

char	*item_value_get(t_map *map, const char *find_name)
{
	t_item	*item;
	char	*get_value;

	item = map->item;
	get_value = NULL;
	while (item != NULL)
	{
		get_value = search_value(item, find_name);
		if (get_value != NULL)
			break ;
		item = item->next;
	}
	return (get_value);
}
