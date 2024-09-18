/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:31 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/18 13:27:37 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

t_token_info	*ft_tokendup(t_token_info *token)
{
	t_token_info	*cp_token;

	cp_token = (t_token_info *)malloc(sizeof(t_token_info));
	cp_token->word = ft_strdup(token->word);
	cp_token->kind = token->kind;
	cp_token->next = NULL;
	return (cp_token);
}

void	token_append_tail(t_node_info *node, t_token_info *cp_token)
{
	t_token_info *search_token;
	
	search_token=node->node_token;
	
	while (search_token->next != NULL)
		search_token=search_token->next;
	search_token->next= cp_token;
}

//最初にEOFトークンを作っておくのはいいかもね。ありようがここには
void	word_node(t_node_info *node, t_token_info *token)
{
	t_token_info	*cp_token;

	cp_token = ft_tokendup(token);
	if (node->node_token == NULL)
		node->node_token = cp_token;
	else
		token_append_tail(node, cp_token);
}

void	append_node(t_node_info *node, t_token_info *token)
{
	if (token->kind == WORD)
		word_node(node, token);
	//	else if(token->kind==OP)
	//		op_node(node,token);
	//	else if(token->kind==RESERVE)
	//		reserve_node(node,token);
	//	else if(token->kind==ROF)
	//		eof_node(node);
}

t_node_info	*make_node(void)
{
	t_node_info	*node;

	node = (t_node_info *)malloc(sizeof(t_node_info));
	node->kind = -1;
	node->next = NULL;
	node->node_token = NULL;
	node->redirects = NULL;
	node->targetfd = -1;
	node->filename = NULL;
	node->filefd = -1;
	node->stashed_targetfd = -1;
	return (node);
}

t_node_info	*parser(t_token_info *token)
{
	t_node_info	*node;
	t_token_info *eof_token;

	node = make_node();
	while (token->kind != ROF)
	{
		append_node(node, token);
		token = token->next;
	}
	eof_token=make_eof_token();
	token_append_tail(node,eof_token);	
	return (node);
}

