/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:19:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/09 16:39:51 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

volatile sig_atomic_t	sig = 0;

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		sig = SIGINT;
		return (ft_printf("\n"), rl_on_new_line(), rl_replace_line("", 0),
			rl_redisplay());
	}
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
