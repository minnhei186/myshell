/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_prepare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:41:20 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/16 14:42:13 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	redirect_type_init(t_prompt_info *info, t_node_info *redirect)
{
	if (redirect->kind == ND_REDIR_OUT)
		redirect_out_init(info, redirect);
	else if (redirect->kind == ND_REDIR_IN)
		redirect_in_init(info, redirect);
	else if (redirect->kind == ND_REDIR_APPEND)
		redirect_append_init(info, redirect);
//	else if (redirect->kind == ND_REDIR_HEREDOC)
//		redirect_heredoc_init(info, redirect);
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
