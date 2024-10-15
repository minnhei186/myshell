/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:16:31 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/15 10:11:53 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

// pipefd[0]: 読み込み, pipefd[1]: 書き込み
// すでにinpipe[1]は前ので閉じられているよ。
//次のnodeがある時に生存させるのはoutpipe[0]



static void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_prompt_info *info,t_node_info *node)
{
	if (node->re_node != NULL)
	{
		if(pipe(node->outpipe)==-1)
		{
			minishell_perror(info,"failed to create a pipe");
			return;
		}
		cpy_pipe(node->re_node->inpipe, node->outpipe);
	}
}

void	prepare_pipe_child(t_node_info *node)
{
	close(node->outpipe[0]);             
	if(dup2(node->inpipe[0], STDIN_FILENO)==-1)
		fatal_error_exit("failed to dup2 a pipe");

	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	if(dup2(node->outpipe[1], STDOUT_FILENO)==-1)
		fatal_error_exit("failed to dup2 a pipe");
	if (node->outpipe[1] != STDOUT_FILENO)
		close(node->outpipe[1]);
}

void	prepare_pipe_parent(t_node_info *node)
{
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	if (node->re_node)
		close(node->outpipe[1]);}
