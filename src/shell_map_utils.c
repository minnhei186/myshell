/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:00:35 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/12 13:39:13 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

// itemの構造上nameがNULLのもので存在するものはない。
size_t	item_len(t_item *item, bool null_value_flag)
{
	size_t	len;

	len = 0;
	while (item)
	{
		if (item->value || null_value_flag)
			len++;
		item = item->next;
	}
	return (len);
}


char	*get_variable_str(const char *name, const char *value)
{
	char	*result;
	size_t	name_len;
	size_t	value_len;
	size_t	total_len;

	name_len = ft_strlen(name);
	if (value != NULL)
	{
		value_len = ft_strlen(value);
		// total_len = nameの長さ + '=' + valueの長さ + 終端文字
		total_len = name_len + 1 + value_len + 1;
	}
	else
	{
		value_len = 0;
		// valueがNULLの場合、'='を含めない
		total_len = name_len + 1; // 終端文字分
	}
	// メモリ割り当てとエラー処理
	result = (char *)malloc(total_len);
	// nameをコピー
	ft_strlcpy(result, name,name_len+1);
	if (value != NULL)
	{
		// '='を追加
		ft_strlcat(result, "=",total_len);
		// valueを追加
		ft_strlcat(result, value,total_len);
	}
	return (result);
}

char	**item2argv(t_item *item)
{
	size_t	item_count;
	size_t	i;
	char	**argv;

	item_count = item_len(item, false);
	argv = (char **)malloc(sizeof(char *) * (item_count + 1));
	i = 0;
	while (i < item_count)
	{
		argv[i] = get_variable_str(item->name, item->value);
		i++;
		item=item->next; // item_count分は必ず存在
	}
	argv[i] = NULL;
	return (argv);
}
