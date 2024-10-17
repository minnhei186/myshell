/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_refunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:43:30 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/17 22:49:05 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

#include <stddef.h>

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    // エラーチェック：ポインタがNULLでないことを確認
    if (dest == NULL || src == NULL)
        return NULL;

    // エラーチェック：nが0の場合、何もせずにdestを返す
    if (n == 0)
        return dest;

    for (i = 0; i < n; i++)
    {
        if (src[i] != '\0')
            dest[i] = src[i];
        else
            break;
    }

    // 残りの部分を'\0'で埋める
    for (; i < n; i++)
        dest[i] = '\0';

    return dest;
}


int ft_strcmp(const char *s1, const char *s2)
{
    // NULLポインタのチェック
    if (s1 == NULL && s2 == NULL)
        return 0; // 両方NULLなら等しいとみなす
    if (s1 == NULL)
        return -1; // s1がNULLの場合、s2より小さいとみなす
    if (s2 == NULL)
        return 1;  // s2がNULLの場合、s1より大きいとみなす

    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

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
	size_t		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	new = (char *)minishell_malloc(sizeof(char) * len + 1);
	while (i < len&&s[i]!='\0')
	{
		new[i]= s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
