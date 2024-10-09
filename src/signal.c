/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:19:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/09 15:09:06 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"
volatile sig_atomic_t sig = 0;


void	handler(int signum)
{
	sig = signum;
	return (ft_printf("\n"), rl_on_new_line(), rl_replace_line("", 0),
		rl_redisplay());
}

void	ready_sigint(void)
{
	struct sigaction	sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error_exit("failed to sigaction");
}

void	init_signal(void)
{
	extern int _rl_echo_control_chars;

	//_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	//if (isatty(STDIN_FILENO))
	//	rl_event_hook = check_signal_state;
	ready_sigint();
}


//main関数
//返り値？
int check_signal_state(void)
{
	if(sig==0)
		return 0;
	else if (sig==SIGINT)
	{
		sig=0;
		rl_replace_line("",0);
		rl_on_new_line();
		rl_redisplay();
		return 0;
	}
	return 0;
}




