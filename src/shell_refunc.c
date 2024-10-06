/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_refunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:43:30 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/05 16:10:15 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void *minishell_malloc(size_t size)
{
	void *pt;

	pt=malloc(size);
	if(pt==NULL)
		fatal_error_exit("failed to allocate memory");
	return pt;
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
