/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:47:50 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/10 19:31:27 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

// open
void	redirect_out_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDOUT_FILENO;
	redirect->filefd = open(redirect->filename->word,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

void	redirect_in_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDIN_FILENO;
	redirect->filefd = open(redirect->filename->word, O_RDONLY, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

void	redirect_append_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDOUT_FILENO;
	redirect->filefd = open(redirect->filename->word,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

void	redirect_type_init(t_prompt_info *info, t_node_info *redirect)
{
	if (redirect->kind == ND_REDIR_OUT)
		redirect_out_init(info, redirect);
	else if (redirect->kind == ND_REDIR_IN)
		redirect_in_init(info, redirect);
	else if (redirect->kind == ND_REDIR_APPEND)
		redirect_append_init(info, redirect);
}

void	init_redirect(t_prompt_info *info, t_node_info *cmd_node)
{
	t_node_info	*redirect_node;

	redirect_node = cmd_node->redirects;
	while (redirect_node != NULL)
	{
		redirect_type_init(info, redirect_node);
		if (info->yourser_err == 1)
			return ;
		redirect_node = redirect_node->redirects;
	}
}

void	prepare_redirect(t_prompt_info *info, t_node_info *node)
{
	while (node != NULL)
	{
		init_redirect(info, node->cmd);
		if (info->yourser_err == 1)
			return ;
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
