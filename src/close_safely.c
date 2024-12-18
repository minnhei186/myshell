/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_safely.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:47 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 15:31:12 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	close_safely(int fd)
{
	int	ret;

	ret = -1;
	if (fd != -1)
	{
		ret = close(fd);
		fd = -1;
	}
	return (ret);
}
