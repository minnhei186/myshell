/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_refunc_first.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:47:39 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 15:48:28 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	*minishell_malloc(size_t size)
{
	void	*pt;

	pt = malloc(size);
	if (pt == NULL)
		fatal_error_exit("failed to allocate memory");
	return (pt);
}

void	*minishell_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*headp;

	i = 0;
	if (size && count > SIZE_MAX / size)
		fatal_error_exit("over_allocate_memory");
	p = minishell_malloc(count * size);
	headp = p;
	while (i < count * size)
	{
		*p = 0;
		p++;
		i++;
	}
	return (headp);
}

char	*minishell_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*p;
	char	*phead;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	p = (char *)minishell_malloc(sizeof(char) * len + 1);
	phead = p;
	while (i < len)
	{
		*p = *s1;
		p++;
		s1++;
		i++;
	}
	*p = '\0';
	return (phead);
}

char	*minishell_strndup(const char *s, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	new = (char *)minishell_malloc(sizeof(char) * len + 1);
	while (i < len && s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
