/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_set_reset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:51:21 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 17:15:09 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	stash_fd(t_prompt_info *info, t_node_info *redirect)
{
	int	max_attempts;
	int	attempts;
	int	newfd;

	max_attempts = 1024;
	attempts = 0;
	while (attempts < max_attempts)
	{
		newfd = dup(redirect->targetfd);
		if (newfd < 0)
		{
			minishell_perror(info, "failed to dup");
			return (-1);
		}
		if (newfd != 0 && newfd != 1 && newfd != 2)
		{
			redirect->stashedfd = newfd;
			return (0);
		}
		close_safely(newfd);
		attempts++;
	}
	minishell_perror(info, "failed to make_new_stashedfd");
	return (-1);
}

void	redirect_do_set(t_prompt_info *info, t_node_info *redirect)
{
	if (stash_fd(info, redirect) < 0)
		return ;
	dup2(redirect->filefd, redirect->targetfd);
	close_safely(redirect->filefd);
}

void	do_redirect(t_prompt_info *info, t_node_info *redirect_node)
{
	while (redirect_node != NULL)
	{
		redirect_do_set(info, redirect_node);
		if (info->yourser_err)
			return ;
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

void	do_reset_redirect(t_node_info *redirect_node)
{
	if (redirect_node == NULL)
		return ;
	do_reset_redirect(redirect_node->redirects);
	if (is_redirect(redirect_node) && redirect_node->stashedfd != -1)
	{
		close_safely(redirect_node->filefd);
		close_safely(redirect_node->targetfd);
		dup2(redirect_node->stashedfd, redirect_node->targetfd);
		close_safely(redirect_node->stashedfd);
	}
}
