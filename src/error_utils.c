/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:09:32 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/05 11:24:17 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

#define ERROR_PRESTR "minishell: "

// void	system_error(char *err_msg,
//			t_prompt_info *info) __attribute__((noreturn));

void	error_set_print(char *err_msg, int error_type, t_prompt_info *info)
{
	info->last_status = errno;
	if (error_type)
		perror(err_msg);
	else
		ft_putendl_fd(err_msg, STDERR_FILENO);
}

// void	system_error(char *err_msg, t_prompt_info *info)
//{
//	error_set_print(err_msg, SYSTEM_ERROR, info);
//	exit(1);
//}

//親プロセスのシステムエラーの場合はfreeなども考えずにexitfree?
//子プロセスはどうするのか？
//とりあえず、何も考えるずに終了する。exitfree
void	perror_prestr(void)
{
	write(STDERR_FILENO,ERROR_PRESTR,ft_strlen(ERROR_PRESTR));
}

void	system_error_exit(char *err_msg)
{
	perror_prestr();
	ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

//こいつはどこで用いるんだろうか？systemエラー以外？（ユーザーエラーとの違いは？
void	err_exit(const char *location, const char *msg, int status)
{
	perror_prestr();
	write(STDERR_FILENO, location, strlen(location));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1); // 改行を追加
	exit(status);
}
