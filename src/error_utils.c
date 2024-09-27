/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:09:32 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/26 19:43:02 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//void	system_error(char *err_msg,
//			t_prompt_info *info) __attribute__((noreturn));

void	error_set_print(char *err_msg, int error_type, t_prompt_info *info)
{
	info->status = errno;
	if (error_type)
		perror(err_msg);
	else
		ft_putendl_fd(err_msg, STDERR_FILENO);
}

void	system_error(char *err_msg, t_prompt_info *info)
{
	error_set_print(err_msg, SYSTEM_ERROR, info);
	exit(1);
}
