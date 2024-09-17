/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:31 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/17 13:29:38 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

t_token_info	*ft_tokendup(t_token_info *src_tk)
{
	t_token_info	root_tk;
	t_token_info	*cp_tk;
	t_token_info	*branch_tk;

	cp_tk = &root_tk;
	while (src_tk->next != NULL)
	{
		branch_tk = (t_token_info *)malloc(sizeof(t_token_info));
		branch_tk->word = ft_strdup(src_tk->word);
		branch_tk->kind = src_tk->kind;
		branch_tk->next = NULL;
		cp_tk->next = branch_tk;
		cp_tk = cp_tk->next;
		src_tk = src_tk->next;
	}
	cp_tk->next = make_eof_token();
	return (root_tk.next);
}

t_node_info	*make_eof_node(void)
{
	t_node_info	*new_node;

	new_node = (t_node_info *)malloc(sizeof(t_node_info));
	new_node->node_tk = NULL;
	new_node->kind = NODE_EOF;
	new_node->next = NULL;
	return (new_node);
}

//ここは本来オペランドなどで,今回はnodeを一つだけ作る
t_node_info	*parser(t_token_info *token)
{
	t_node_info	root_node;
	t_node_info	*node;
	t_node_info	*new_node;

	node = &root_node;
	new_node = (t_node_info *)malloc(sizeof(t_node_info));
	new_node->node_tk = ft_tokendup(token);
	new_node->kind = SIMPLE_CMD;
	new_node->next = NULL;
	node->next = new_node;
	node = node->next;
	new_node = make_eof_node();
	node->next = new_node;
	return (root_node.next);
}
