/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:47:50 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/23 15:14:22 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

// redirect_zone
void	redirect_open_set(t_node_info *redirect)
{
	redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY, 0644);
	redirect->targetfd = STDOUT_FILENO;//openするだけここでは
}

void	init_redirect(t_node_info *node)
{
	while (node->redirects != NULL)
	{
		redirect_open_set(node->redirects);
		node = node->redirects;
	}
}

//初期設定であるstdoutをfilefdにdup２
void	redirect_do_set(t_node_info *redirect)
{
	redirect->stashedfd = fcntl(redirect->targetfd, F_DUPFD, 10);
	dup2(redirect->filefd, redirect->targetfd);
}

void	do_redirect(t_node_info *node)
{
	while (node->redirects != NULL)
	{
		redirect_do_set(node->redirects);
		node = node->redirects;
	}
}

void	prepare_redirect(t_node_info *node)
{
	while (1)
	{
		init_redirect(node->cmd);
		if (node->re_node == NULL)
			break ;
		node = node->re_node;
	}
}

void	redirect_reset_set(t_node_info *redirect)
{
	dup2(redirect->stashedfd, redirect->targetfd);
}

void	do_reset_redirect(t_node_info *node)
{
	while (node->redirects != NULL)
	{
		redirect_reset_set(node->redirects);
		node = node->redirects;
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
