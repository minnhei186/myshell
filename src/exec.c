/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:28:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/20 17:25:56 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	wait_all_processes(int last_pid)
{
	int		status;
	int		last_status;
	pid_t	wpid;

	last_status = 0;
	while ((wpid = waitpid(-1, &status, 0)) > 0)
	{
		if(WEXITSTATUS(status)==131)
		{
			write(STDOUT_FILENO,"Quit: 3",7);
			write(STDOUT_FILENO,"\n",1);
		}
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			else
				last_status = status; // その他の場合
		}
	}
	return (last_status);
}

void	exec(t_prompt_info *info, t_node_info *node)
{
	int	last_pid;

	if (node->re_node == NULL && is_builtin(node))
		exec_builtin(info, node);
	else
	{
		last_pid = command_comunication(info, node);
		if (info->yourser_err)
			return ;
		info->last_status = wait_all_processes(last_pid);
	}
}
