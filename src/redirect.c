/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:47:50 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/29 18:50:29 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

// open
void	redirect_out_init(t_node_info *redirect)
{
	redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY, 0644);
	redirect->targetfd = STDOUT_FILENO;
}

void	redirect_in_init(t_node_info *redirect)
{
	redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY, 0644);
	redirect->targetfd = STDIN_FILENO;
}

void	redirect_type_init(t_node_info *redirect)
{
	if (redirect->kind == ND_REDIR_OUT)
		redirect_out_init(redirect);
	else if (redirect->kind == ND_REDIR_IN)
		redirect_in_init(redirect);
}

void	init_redirect(t_node_info *cmd_node)
{
	t_node_info	*redirect_node;

	redirect_node = cmd_node->redirects;
	while (redirect_node != NULL)
	{
		redirect_type_init(redirect_node);
		redirect_node = redirect_node->redirects;
	}
}

void	prepare_redirect(t_node_info *node)
{
	while (node != NULL)
	{
		init_redirect(node->cmd);
		node = node->re_node;
	}
}

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

// reset

void	redirect_reset_set(t_node_info *redirect)
{
	dup2(redirect->stashedfd, redirect->targetfd);
}

void	do_reset_redirect(t_node_info *cmd_node)
{
	t_node_info	*redirect_node;

	redirect_node = cmd_node->redirects;
	while (redirect_node != NULL)
	{
		redirect_reset_set(redirect_node);
		redirect_node = redirect_node->redirects;
	}
}

void	reset_redirect(t_node_info *node)
{
	while (1)
	{
		do_reset_redirect(node->cmd);
		if (node->re_node == NULL)
			break ;
		node = node->re_node;
	}
}
