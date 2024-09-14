/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:09:32 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/14 13:09:58 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	error_set(char *err_msg, int error_type, t_prompt_info *info)
{
	info->status = errno;
	if (error_type)
		perror(err_msg);
	else
		ft_putendl_fd(err_msg, STDERR_FILENO);
}
