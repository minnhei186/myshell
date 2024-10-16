/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:01:24 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/15 13:54:08 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

t_token_info	*redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token)
{
	t_token_info	*now_token;

	now_token = token;
	if (type_redirect_op(token) == 1)
		now_token = output_redirect_node(info, node, token);
	else if (type_redirect_op(token) == 2)
		now_token = input_redirect_node(info, node, token);
	else if (type_redirect_op(token) == 3)
		now_token = append_redirect_node(info, node, token);
	else if(type_redirect_op(token)==4)
		now_token = heredoc_redirect_node(info, node, token);

	return (now_token);
}

t_token_info	*op_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token)
{
	t_token_info	*now_token;

	now_token = token;
	if (type_redirect_op(token) != 0)
		now_token = redirect_node(info, node, token);
	if ((ft_strncmp(token->word, "|", 1) == 0))
		eof_token(node);
	return (now_token);
}

void	word_token(t_node_info *node, t_token_info *token)
{
	t_token_info	*cp_token;

	cp_token = ft_tokendup(token);
	if (node->node_token == NULL)
		node->node_token = cp_token;
	else
		token_append_tail(node, cp_token);
}

void	eof_token(t_node_info *node)
{
	t_token_info	*eof_token;

	eof_token = (t_token_info *)minishell_calloc(1, sizeof(t_token_info));
	eof_token->word = NULL;
	eof_token->kind = ROF;
	eof_token->next = NULL;
	if (node->node_token == NULL)
		node->node_token = eof_token;
	else
		token_append_tail(node, eof_token);
}

t_token_info	*append_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token)
{
	t_token_info	*now_token;

	now_token = token;
	if (token->kind == WORD)
		word_token(node, token);
	else if (token->kind == OP)
		now_token = op_node(info, node, token);
	else if (token->kind == ROF)
		eof_token(node);
	return (now_token);
}
