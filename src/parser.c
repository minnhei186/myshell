/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:31 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/06 18:33:22 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

t_node_info	*make_node(void)
{
	t_node_info	*node;

	node = (t_node_info *)minishell_malloc(sizeof(t_node_info));
	node->kind = -1;
	// pipe_node
	node->re_node = NULL;
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	;
	// cmd_node
	node->cmd = NULL;
	node->node_token = NULL;
	// redirects_node
	node->redirects = NULL;
	node->targetfd = -1;
	node->filename = NULL;
	node->delimiter = NULL;
	node->filefd = -1;
	node->stashedfd = -1;
	return (node);
}

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
	t_token_info	*search_token;

	search_token = node->node_token;
	while (search_token->next != NULL)
		search_token = search_token->next;
	search_token->next = cp_token;
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

	eof_token = (t_token_info *)ft_calloc(1, sizeof(t_token_info));
	eof_token->word = NULL;
	eof_token->kind = ROF;
	eof_token->next = NULL;
	if (node->node_token == NULL)
		node->node_token = eof_token;
	else
		token_append_tail(node, eof_token);
}

int	type_redirect_op(t_token_info *token)
{
	if (strcmp(token->word, ">") == 0)
		return (1);
	else if (strcmp(token->word, "<") == 0)
		return (2);
	return (0);
}

int	is_pipe_op(t_token_info *token)
{
	if (strcmp(token->word, "|") == 0)
		return (1);
	return (0);
}

void	redirect_append_tail(t_node_info *node, t_node_info *append_redirect)
{
	t_node_info	*search_redirect;

	search_redirect = node->redirects;
	while (search_redirect->redirects != NULL)
		search_redirect = search_redirect->redirects;
	search_redirect->redirects = append_redirect;
}

t_token_info	*output_redirect_node(t_prompt_info *info,t_node_info *node, t_token_info *token)
{
	t_node_info	*redirect_node;

	if (token->next->kind != WORD)//ここを先に判定！//何も作らず何も追加せず返す
	{
		parser_error(info,token->word);
		return (NULL);
	}


	redirect_node = make_node();
	redirect_node->kind = ND_REDIR_OUT;
	redirect_node->delimiter=ft_tokendup(token);
	token = token->next;
	redirect_node->filename = ft_tokendup(token);
	if (node->redirects == NULL)
		node->redirects = redirect_node;
	else
		redirect_append_tail(node, redirect_node);
	return (token);
}

//構文と生成規則による
//先に判定した方がいいかも、作らず追加せずに返してあげる
t_token_info	*input_redirect_node(t_prompt_info *info,t_node_info *node, t_token_info *token)
{
	t_node_info	*redirect_node;

	if (token->next->kind != WORD)//ここを先に判定！//何も作らず何も追加せず返す
	{
		parser_error(info,token->word);
		return (NULL);
	}
	redirect_node = make_node();
	redirect_node->kind = ND_REDIR_IN;
	redirect_node->delimiter=ft_tokendup(token);
	token = token->next;
		redirect_node->filename = ft_tokendup(token);
	if (node->redirects == NULL)
		node->redirects = redirect_node;
	else
		redirect_append_tail(node, redirect_node);
	return (token);
}


t_token_info	*redirect_node(t_prompt_info *info,t_node_info *node, t_token_info *token)
{
	t_token_info	*now_token;

	now_token = token;
	if (type_redirect_op(token) == 1)
		now_token = output_redirect_node(info,node, token);
	 else if(type_redirect_op(token)==2)
		now_token=input_redirect_node(info,node,token);
	return (now_token);
}

// cmdではなくredirects_nodeにおいて
// 構文と生成規則による？
t_token_info	*op_node(t_prompt_info *info,t_node_info *node, t_token_info *token)
{
	t_token_info	*now_token;

	//リダイレクトかどうか
	now_token = token;
	if (type_redirect_op(token) != 0)
		now_token = redirect_node(info,node, token);
	//パイプかどうか
	if ((ft_strncmp(token->word, "|",1) == 0))
		eof_token(node);
	return (now_token);
}

// tokenにpipeがきたらそれはeofトークンとして処理しよう。
t_token_info	*append_node(t_prompt_info *info,t_node_info *node, t_token_info *token)
{
	t_token_info	*now_token;

	now_token = token;
	if (token->kind == WORD)
		word_token(node, token);
	else if (token->kind == OP)
		now_token = op_node(info,node, token); 
	else if (token->kind == ROF)
		eof_token(node);
	return (now_token);
}

t_node_info	*prompt_parser(t_prompt_info *info,t_token_info *token)
{
	t_node_info		*command_node;
	t_token_info	*now_token;

	command_node = make_node();
	command_node->kind = ND_SIMPLE_CMD;
	while (token->next != NULL)
	{
		now_token = append_node(info,command_node, token);
		if(info->yourser_err==1)//ここを追加　//ここでもう処理終わりとするerr
			return command_node;
		if ((ft_strncmp(token->word, "|",1) == 0))
			return (command_node);
		token = now_token->next;
	}
	append_node(info,command_node, token);
	return (command_node);
}

t_token_info	*find_pipe(t_token_info *token)
{
	while (token->next != NULL)
	{
		if (ft_strncmp(token->word, "|",1) == 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

t_node_info	*parser(t_prompt_info *info,t_token_info *token)
{
	t_node_info		*node;
	t_token_info	*now_token;

	node = make_node();
	node->kind = ND_PIPE;
	node->cmd = prompt_parser(info,token);
	now_token = find_pipe(token);
	if (now_token != NULL)
	{
		now_token = now_token->next;
		node->re_node = parser(info,now_token);
	}
	return (node);
}
