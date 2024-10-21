/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:19:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/21 14:52:50 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//ここら辺考える必要があるな。
volatile sig_atomic_t	g_sig_status =READLINE;

int	event(void)
{
	return (0);
}

void	handler(int signum)
{
	(void)signum;
	if (g_sig_status == HEREDOC)
	{
		g_sig_status = SIG_INT;
		rl_replace_line("", 0);
		rl_done = 1;
	}
	else if(g_sig_status==IN_CMD)//親プロセスのコマンドあと
	{
		g_sig_status=SIG_INT;
		write(STDOUT_FILENO, "\n", 1);
		ft_printf("command_signal_now\n");
	}
	else
	{
		g_sig_status = SIG_INT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	reset_signal(int signum)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		fatal_error_exit("failed to sigemptyset");
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error_exit("failed to sigaciton");
}


void	ignore_signal(int signum)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		fatal_error_exit("failed to sigemptyset");
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error_exit("failed to sigaction");
}

void	ready_signal(int signum)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		fatal_error_exit("failed to sigemptyset");
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error_exit("failed to sigaction");
}

void	init_signal(void)
{
	if (isatty(STDIN_FILENO))
		rl_event_hook = event;
	rl_catch_signals = 0;
	rl_outstream = stderr;
	ignore_signal(SIGQUIT);
	ready_signal(SIGINT);
}

void destroy_signal(void)
{
	reset_signal(SIGQUIT);
	reset_signal(SIGINT);
}

