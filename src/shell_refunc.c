/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_refunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:43:30 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/05 13:47:01 by hosokawa         ###   ########.fr       */
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
