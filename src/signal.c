/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:19:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/16 14:50:25 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

volatile sig_atomic_t g_sig_status = IN_CMD;

void	handler(int signum)
{
	if (g_sig_status == HEREDOC)
	{
		// ヒアドキュメント入力中に Ctrl+C が押された場合
		g_sig_status= SIG_INT;
		return;
	}
	//else if (g_sig_status== IN_CMD)
	//{
	//	// コマンド入力中に Ctrl+C が押された場合
	//	ft_printf("\n");
	//	rl_replace_line("", 0);
	//	rl_redisplay();
	//	g_sig_status= SIG_INT;
	//	return ;
	//}
	g_sig_status= SIG_INT;
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ready_signal(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		fatal_error_exit("failed to sigemptyset");
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error_exit("failed to sigaction");
}

void	init_signal(void)
{
	rl_outstream = stderr;
	ready_signal();
}
