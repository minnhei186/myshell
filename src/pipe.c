/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:16:31 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/24 14:29:06 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//親プロセスは再起によって一元化されている。一つのプロセスとしてwait_pid

//一番最初の実行とそれ以降の実行（パイプ)
//どのように？
//

static void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_node_info *node)
{
	if (node->re_node != NULL)
	{
		pipe(node->outpipe);
		cpy_pipe(node->re_node->inpipe, node->outpipe);
	}
}

// pipefd[0]: 読み込み, pipefd[1]: 書き込み
// すでにinpipe[1]は前ので閉じられているよ。
void	prepare_pipe_child(t_node_info *node)
{
	close(node->outpipe[0]);             
	dup2(node->inpipe[0], STDIN_FILENO); 
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	dup2(node->outpipe[1], STDOUT_FILENO);
	if (node->outpipe[1] != STDOUT_FILENO)
		close(node->outpipe[1]);
}

void	prepare_pipe_parent(t_node_info *node)
{
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	if (node->re_node)
		close(node->outpipe[1]);//次のnodeがある時に生存させるのはoutpipe[0]
}
