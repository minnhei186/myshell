/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:16:31 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 15:17:01 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

static void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_prompt_info *info, t_node_info *node)
{
	if (node->re_node != NULL)
	{
		if (pipe(node->outpipe) == -1)
		{
			minishell_perror(info, "failed to create a pipe");
			return ;
		}
		cpy_pipe(node->re_node->inpipe, node->outpipe);
	}
}

void	prepare_pipe_child(t_node_info *node)
{
	close_safely(node->outpipe[0]);
	if (dup2(node->inpipe[0], STDIN_FILENO) == -1)
		fatal_error_exit("failed to dup2 a pipe");
	if (node->inpipe[0] != STDIN_FILENO)
		close_safely(node->inpipe[0]);
	if (dup2(node->outpipe[1], STDOUT_FILENO) == -1)
		fatal_error_exit("failed to dup2 a pipe");
	if (node->outpipe[1] != STDOUT_FILENO)
		close_safely(node->outpipe[1]);
}

void	prepare_pipe_parent(t_node_info *node)
{
	if (node->inpipe[0] != STDIN_FILENO)
		close_safely(node->inpipe[0]);
	if (node->re_node)
		close_safely(node->outpipe[1]);
}
