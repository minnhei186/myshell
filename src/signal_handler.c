/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:29:05 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 13:35:15 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

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
	else if (g_sig_status == IN_CMD)
	{
		g_sig_status = SIG_INT;
		write(STDOUT_FILENO, "\n", 1);
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
