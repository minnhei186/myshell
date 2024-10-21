/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_set_reset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:51:21 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/21 15:38:04 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	redirect_do_set(t_node_info *redirect)
{
	redirect->stashedfd = fcntl(redirect->targetfd, F_DUPFD, 10); // stdoutの保持
	dup2(redirect->filefd, redirect->targetfd);
	close(redirect->filefd);
}

void	do_redirect(t_node_info *redirect_node)
{
	while (redirect_node != NULL)
	{
		redirect_do_set(redirect_node);
		redirect_node = redirect_node->redirects;
	}
}

bool	is_redirect(t_node_info *node)
{
	if (node->kind == ND_REDIR_OUT)
		return (true);
	else if (node->kind == ND_REDIR_IN)
		return (true);
	else if (node->kind == ND_REDIR_APPEND)
		return (true);
	else if (node->kind == ND_REDIR_HEREDOC)
		return (true);
	return (false);
}

void do_reset_redirect(t_node_info *redirect_node)
{
	if(redirect_node==NULL)
		return;
	do_reset_redirect(redirect_node->redirects);
	if(is_redirect(redirect_node))
	{
		close(redirect_node->filefd);
		close(redirect_node->targetfd);
		dup2(redirect_node->stashedfd, redirect_node->targetfd);
		close(redirect_node->stashedfd);//新たに追加
	}
	else
		printf("reset_error\n");
}


//void	do_reset_redirect(t_node_info *node)
//{
//	if (node->redirects == NULL)
//		return ;
//	do_reset_redirect(node->redirects);
//	if (is_redirect(node))
//	{
//		close(node->filefd);
//		close(node->targetfd);
//		dup2(node->stashedfd, node->targetfd);
//	}
//	else
//		printf("error\n");//こいつだ！！！
//}
