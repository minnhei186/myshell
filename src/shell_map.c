/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:19:34 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/09 16:55:08 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

typedef struct s_item	t_item;

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
	new_item->name =(char *) minishell_strdup(name);
	new_item->value = (char *)minishell_strdup(value);
	return (new_item);
}

t_map	*minishell_make_map(void)
{
	t_map	*new_map;

	new_map = (t_map *)minishell_malloc(sizeof(t_map));
	new_map->item = NULL;
	new_map->envp= NULL;
	return (new_map);
}

char	*search_value(t_item *item, const char *find_name)
{
	char	*new_value;

	if (ft_strncmp(item->name, find_name, sizeof(find_name)) == 0)
	{
		new_value = ft_strdup(item->value);
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

//まずそれを持っているか考え、あったら更新なかったら追加
//重要なのは実態のメンバnextにアクセスすること。

//ここも修正が必要
//ここではユーザーエラーは必要ないためinfoはいらない?
void item_set(t_map *map, const char *name, const char *value)
{
	t_item	*new_item;
	t_item	*old_item;
	t_item	*last_item;

	old_item = map->item;
	last_item = NULL;
	new_item = make_unit_item(name, value);
	while (old_item != NULL)
	{
		if (ft_strncmp(name, old_item->name, sizeof(old_item->name)) == 0)
		{
			free(old_item->value);
			old_item->value = minishell_strdup(value);
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
		if (ft_strncmp(item->name, name, sizeof(name)) == 0)
		{
			if (prev == NULL) //繋ぎ合わせるものがない時は？
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
		//ここ
		name = minishell_strndup(string, middle_qual - string);
		value = minishell_strdup(middle_qual + 1);
	}
	item_set(map, name, value);//ここでセットされる。しかしfreeはする
	free(name);
	free(value);
}
