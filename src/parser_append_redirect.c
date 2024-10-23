/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_append_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:05:35 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 13:21:50 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

t_token_info	*output_redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token)
{
	t_node_info	*redirect_node;

	if (token->next->kind != WORD)
	{
		parser_error(info, token->word);
		return (NULL);
	}
	redirect_node = make_node();
	redirect_node->kind = ND_REDIR_OUT;
	redirect_node->delimiter = ft_tokendup(token);
	token = token->next;
	redirect_node->filename = ft_tokendup(token);
	if (node->redirects == NULL)
		node->redirects = redirect_node;
	else
		redirect_append_tail(node, redirect_node);
	return (token);
}

t_token_info	*input_redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token)
{
	t_node_info	*redirect_node;

	if (token->next->kind != WORD)
	{
		parser_error(info, token->word);
		return (NULL);
	}
	redirect_node = make_node();
	redirect_node->kind = ND_REDIR_IN;
	redirect_node->delimiter = ft_tokendup(token);
	token = token->next;
	redirect_node->filename = ft_tokendup(token);
	if (node->redirects == NULL)
		node->redirects = redirect_node;
	else
		redirect_append_tail(node, redirect_node);
	return (token);
}

t_token_info	*append_redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token)
{
	t_node_info	*redirect_node;

	if (token->next->kind != WORD)
	{
		parser_error(info, token->word);
		return (NULL);
	}
	redirect_node = make_node();
	redirect_node->kind = ND_REDIR_APPEND;
	redirect_node->delimiter = ft_tokendup(token);
	token = token->next;
	redirect_node->filename = ft_tokendup(token);
	if (node->redirects == NULL)
		node->redirects = redirect_node;
	else
		redirect_append_tail(node, redirect_node);
	return (token);
}

t_token_info	*heredoc_redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token)
{
	t_node_info	*redirect_node;

	if (token->next->kind != WORD)
	{
		parser_error(info, token->word);
		return (NULL);
	}
	redirect_node = make_node();
	redirect_node->kind = ND_REDIR_HEREDOC;
	redirect_node->delimiter = ft_tokendup(token->next);
	if (ft_strchr(redirect_node->delimiter->word, SINGLE_QUOTE) == NULL
		&& ft_strchr(redirect_node->delimiter->word, DOUBLE_QUOTE) == NULL)
		redirect_node->is_delim_unquoted = true;
	token = token->next;
	redirect_node->filename = ft_tokendup(token);
	if (node->redirects == NULL)
		node->redirects = redirect_node;
	else
		redirect_append_tail(node, redirect_node);
	return (token);
}
