/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 07:14:38 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/24 07:14:38 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	char	*h;

	h = (char *)s;
	while (*s && ft_strchr(accept, *s))
		s++;
	return (s - h);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_strchr(reject, s[i]))
		i++;
	return (i);
}

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char	*end;

	if (!str)
		str = *saveptr;
	if (!*str)
	{
		*saveptr = str;
		return (NULL);
	}
	str += ft_strspn(str, delim);
	if (!*str)
	{
		*saveptr = str;
		return (NULL);
	}
	end = str + ft_strcspn(str, delim);
	if (!*end)
	{
		*saveptr = end;
		return (str);
	}
	*end++ = '\0';
	*saveptr = end;
	return (str);
}
