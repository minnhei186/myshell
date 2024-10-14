/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_memory_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:40:33 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 16:16:31 by hosokawa         ###   ########.fr       */
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
		new = minishell_calloc(count + 1, sizeof(char));
		return (new);
	}
	i = ft_strlen(old);
	if (i > SIZE_MAX - count - 1)
		return (NULL);
	new = minishell_calloc(i + count + 1, sizeof(char));
	ft_strlcpy(new, old, i + 1);
	free(old);
	return (new);
}

char	*append_char(char *old, char append_c)
{
	char	*new;
	int		i;

	if (old == NULL)
	{
		new = ft_char_recalloc(old, 1);
		new[0] = append_c;
	}
	else
	{
		new = ft_char_recalloc(old, 1);
		if (new == NULL)
			return (NULL);
		i = ft_strlen(new);
		new[i] = append_c;
	}
	return (new);
}
