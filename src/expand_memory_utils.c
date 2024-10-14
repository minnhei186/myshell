/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_memory_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:40:33 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 14:50:58 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

char	*ft_char_recalloc(char *old, size_t count)
{
	char	*new;
	size_t	i;

	if (count == SIZE_MAX)
		return (NULL);
	if (old == NULL)
	{
		new = ft_calloc(count + 1, sizeof(char));
		if (new == NULL)
			return (NULL);
		return (new);
	}
	i = ft_strlen(old);
	if (i > SIZE_MAX - count - 1) //右辺が-1だとラウンドアップされ検出できない
		return (NULL);
	new = ft_calloc(i + count + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	strlcpy(new, old, i + 1); // null終端文字を含めること
	free(old);
	return (new);
}

char	*append_char(char *old, char append_c)
{
	char	*new;
	int		i;

	new = ft_char_recalloc(old, 1);
	if (new == NULL)
		return (NULL);
	if (old == NULL)
		new[0] = append_c;
	else
	{
		//すでにoldはfreeずみ
		i = ft_strlen(new);
		new[i] = append_c;
	}
	return (new);
}
