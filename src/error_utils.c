/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:09:32 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/05 13:44:08 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

#define ERROR_PRESTR "minishell: "

void	fatal_error_exit(char *err_msg) __attribute__((noreturn));

void	perror_prestr(void)
{
	write(STDERR_FILENO, ERROR_PRESTR, ft_strlen(ERROR_PRESTR));
}

void	fatal_error_exit(char *err_msg)
{
	perror_prestr();
	write(STDERR_FILENO,err_msg,ft_strlen(err_msg));
	write(STDERR_FILENO,"\n",ft_strlen("\n"));
	exit(EXIT_FAILURE);
}

//こいつはどこで用いるんだろうか？systemエラー以外？（ユーザーエラーとの違いは？
//システムコールエラーでも、なぜstatusでexit？
// void	err_exit(const char *location, const char *msg, int status)
//{
//	perror_prestr();
//	write(STDERR_FILENO, location, strlen(location));
//	write(STDERR_FILENO, ": ", 2);
//	write(STDERR_FILENO, msg, strlen(msg));
//	write(STDERR_FILENO, "\n", 1); // 改行を追加
//	exit(status);
//}
